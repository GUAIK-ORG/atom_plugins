#include "tcpclient.h"
#include "keepalive.h"
#include <QAbstractSocket>
#include "ilog.h"

TcpClient::TcpClient(QString remoteIp, quint16 remotePort, QObject *parent)
    : QObject(parent)
    , m_isRunning(false)
    , m_remoteIp(remoteIp)
    , m_remotePort(remotePort)
    , m_isNeedReconnect(false)
{
    connect(&m_socket, &QTcpSocket::connected, this, &TcpClient::onConnected, Qt::QueuedConnection);
    connect(&m_socket, &QTcpSocket::disconnected, this, &TcpClient::onDisconnected, Qt::QueuedConnection);
    connect(&m_socket, &QTcpSocket::readyRead, this, &TcpClient::onReadyRead, Qt::DirectConnection);
    connect(&m_checkStateTimer, &QTimer::timeout, this, &TcpClient::onCheckState, Qt::QueuedConnection);

}

void TcpClient::registerStateProcesser(std::function<void (TCP_CONNECT_STATE)> cb)
{
    m_stateProcesserMutex.lock();
    m_stateProcessers.append(cb);
    m_stateProcesserMutex.unlock();
}

void TcpClient::registerReadProcesser(std::function<void (const QByteArray &)> cb)
{
    m_readProcesserMutex.lock();
    m_readProcessers.append(cb);
    m_readProcesserMutex.unlock();
}

int TcpClient::start()
{
    if (m_isRunning) return -1;
    m_isRunning = true;
    m_socket.connectToHost(m_remoteIp, m_remotePort);
    m_checkStateTimer.start(1000);
    return 0;
}

void TcpClient::stop()
{
    if (!m_isRunning) return;
    m_isRunning = false;
    m_socket.close();
    m_socket.abort();
}

void TcpClient::send(const QByteArray &data)
{
    m_socket.write(data);
}

void TcpClient::free()
{
    this->stop();
}

void TcpClient::callStateProcessers(TCP_CONNECT_STATE state)
{
    m_stateProcesserMutex.lock();
    for(QVector<std::function<void(TCP_CONNECT_STATE)>>::iterator processer=m_stateProcessers.begin(); processer!=m_stateProcessers.end(); ++processer) {
        (*processer)(state);
    }
    m_stateProcesserMutex.unlock();
}

void TcpClient::onConnected()
{
    aDebug() << "enableKeepalive state:" << enableKeepalive(m_socket.socketDescriptor());
    callStateProcessers(TCP_CONNECT_STATE::CONNECTED);
}

void TcpClient::onDisconnected()
{
    callStateProcessers(TCP_CONNECT_STATE::UNCONNECTED);
}

void TcpClient::onReadyRead()
{
    QByteArray data = m_socket.readAll();
    m_readProcesserMutex.lock();
    for(QVector<std::function<void (const QByteArray &)>>::iterator processer=m_readProcessers.begin(); processer!=m_readProcessers.end(); ++processer) {
        (*processer)(data);
    }
    m_readProcesserMutex.unlock();
}

void TcpClient::onCheckState()
{
    switch (m_socket.state()) {
    case QAbstractSocket::UnconnectedState:
        callStateProcessers(TCP_CONNECT_STATE::UNCONNECTED);
        if (m_isNeedReconnect) {
            m_socket.close();
            m_socket.abort();
            m_socket.connectToHost(m_remoteIp, m_remotePort);
        }
        break;

    case QAbstractSocket::HostLookupState:
        break;

    case QAbstractSocket::ConnectingState:
        break;

    case QAbstractSocket::ConnectedState:
        callStateProcessers(TCP_CONNECT_STATE::CONNECTED);
        break;

    case QAbstractSocket::BoundState:
        break;

    case QAbstractSocket::ListeningState:
        break;

    case QAbstractSocket::ClosingState:
        break;
    }
}
