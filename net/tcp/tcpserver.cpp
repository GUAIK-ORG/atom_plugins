#include "tcpserver.h"
#include <QThread>
#include "ilog.h"

TCPServer::TCPServer(quint16 port, QObject* parent)
    : QTcpServer(parent)
    , m_isRunning(false)
    , m_port(port)
{}

void TCPServer::registerReadProcesser(std::function<void (const QByteArray &)> cb)
{
    m_readProcesserMutex.lock();
    m_readProcessers.append(cb);
    m_readProcesserMutex.unlock();
}

int TCPServer::start()
{
    if (m_isRunning) return -1;

    if (this->listen(QHostAddress::Any, m_port)) {
        m_isRunning = true;
        return 0;
    }
    return -1;
}

void TCPServer::stop()
{
    if (!m_isRunning) return;
    m_isRunning = false;
    m_sessMutex.lock();

    const auto keys = m_sessions.keys();
    for(auto&& key: keys) {
        m_sessions[key]->quit();
    }
    for(auto&& key: keys) {
        m_sessions[key]->wait();
    }
    for(auto&& key: keys) {
        delete m_sessions[key];
    }
    m_sessions.clear();

    m_sessMutex.unlock();
    this->close();
}

void TCPServer::send(const QByteArray &data)
{
    m_sessMutex.lock();
    for(QMap<int, Session*>::iterator sess=m_sessions.begin(); sess!=m_sessions.end(); ++sess) {
        sess.value()->send(data);
    }
    m_sessMutex.unlock();
}

void TCPServer::free()
{
    this->stop();
}

void TCPServer::incomingConnection(qintptr socketDescriptor)
{
    Session* sess = new Session(socketDescriptor);
    connect(sess, &Session::disconnected, this, &TCPServer::onDisconnected, Qt::QueuedConnection);
    connect(sess, &Session::readyRead, this, &TCPServer::onReadyRead, Qt::DirectConnection);
    connect(sess, &Session::finished, sess, &Session::deleteLater);

    m_sessMutex.lock();
    if (m_sessions.contains(socketDescriptor)) {
        m_sessions[socketDescriptor]->quit();
        m_sessions[socketDescriptor]->wait();
        delete m_sessions[socketDescriptor];
        m_sessions.remove(socketDescriptor);
    }
    m_sessions.insert(static_cast<int>(socketDescriptor), sess);
    aDebug() << "incomingConnection -> session count:" << m_sessions.size() << " fd:" << (int)socketDescriptor;
    m_sessMutex.unlock();

    sess->start();
}

void TCPServer::onDisconnected(int fd)
{
    m_sessMutex.lock();
    m_sessions[fd]->quit();
    m_sessions[fd]->wait();
    delete m_sessions[fd];
    m_sessions.remove(fd);
    aDebug() << "onDisconnected -> session count:" << m_sessions.size() << "fd:" << fd;
    m_sessMutex.unlock();
}

void TCPServer::onReadyRead(int fd, const QByteArray &data)
{
    Q_UNUSED(fd);
    m_readProcesserMutex.lock();
    for(QVector<std::function<void (const QByteArray &)>>::iterator it=m_readProcessers.begin(); it!=m_readProcessers.end(); ++it) {
        (*it)(data);
    }
    m_readProcesserMutex.unlock();
}
