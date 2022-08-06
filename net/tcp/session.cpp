#include "session.h"
#include "keepalive.h"
#include "ilog.h"

Session::Session(qintptr fd, QObject *parent)
    : QThread(parent)
    , m_fd(fd)
{

}

void Session::send(const QByteArray &data)
{
    emit sendData(data);
}

void Session::run()
{
    aDebug() << "new tcp session";
    m_socket = new TcpSocket();
    m_socket->setSocketDescriptor(m_fd);
    // 启动心跳检测
    enableKeepalive(m_fd);

    connect(m_socket, &QTcpSocket::readyRead, this, &Session::onReadyRead, Qt::DirectConnection);
    connect(m_socket, &QTcpSocket::disconnected, this, &Session::onDisconnected, Qt::QueuedConnection);
    connect(this, &Session::sendData, m_socket, &TcpSocket::onSendData, Qt::QueuedConnection);

    // 启动事件循环
    exec();
    m_socket->close();
    delete m_socket;
}

void Session::onReadyRead()
{
    QByteArray data = m_socket->readAll();
    emit readyRead(static_cast<int>(m_fd), data);
}

void Session::onDisconnected()
{
    emit disconnected(static_cast<int>(m_fd));
    // 断开连接后退出事件循环
    quit();
}
