#include "netservice.h"
#include "ilog.h"
#include "tcp/tcpserver.h"
#include "tcp/tcpclient.h"
#include <QMutexLocker>

NetService::NetService(QObject *parent) : QObject(parent)
{
    m_idGenerator.fetchAndStoreOrdered(0);
}

void NetService::free()
{
    QMutexLocker _(&m_mutex);
    for (NET_OBJ_MAP::Iterator iter=m_objMap.begin(); iter!=m_objMap.end(); ++iter) {
        iter.value()->obj->free();
    }
    m_objMap.clear();
}

int NetService::newTCPServer(quint16 port)
{
    int id = m_idGenerator.fetchAndAddOrdered(1);

    QMutexLocker _(&m_mutex);
    if (m_objMap.contains(id)) return -1;
    m_objMap.insert(id, QSharedPointer<NetObject>(
                        new NetObject(QSharedPointer<NetBase>(
                                          new TCPServer(port)), TCP_SERVER)));
    return id;
}

int NetService::newTCPClient(QString remoteIp, quint16 remotePort)
{
    int id = m_idGenerator.fetchAndAddOrdered(1);

    QMutexLocker _(&m_mutex);
    if (m_objMap.contains(id)) return -1;
    m_objMap.insert(id, QSharedPointer<NetObject>(
                        new NetObject(QSharedPointer<NetBase>(
                                          new TcpClient(remoteIp, remotePort)), TCP_CLIENT)));
    return id;
}

int NetService::enableTCPClientReconnect(int id)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id) || m_objMap[id]->type != NET_OBJECT_TYPE::TCP_CLIENT) return -1;
    dynamic_cast<TcpClient*>(m_objMap[id]->obj.data())->enableReconnect();
    return 0;
}

int NetService::registerTCPClientStateProcesser(int id, std::function<void (TCP_CONNECT_STATE)> cb)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id) || m_objMap[id]->type != NET_OBJECT_TYPE::TCP_CLIENT) return -1;
    dynamic_cast<TcpClient*>(m_objMap[id]->obj.data())->registerStateProcesser(cb);
    return 0;
}

int NetService::bindTCPClientTag(int id, QString tag)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id) || m_objMap[id]->type != NET_OBJECT_TYPE::TCP_CLIENT) return -1;
    dynamic_cast<TcpClient*>(m_objMap[id]->obj.data())->bindTag(tag);
    return 0;
}

QString NetService::getTCPClientTag(int id)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id) || m_objMap[id]->type != NET_OBJECT_TYPE::TCP_CLIENT) return QString("");
    return dynamic_cast<TcpClient*>(m_objMap[id]->obj.data())->getTag();
}

NET_OBJ_MAP NetService::getObjMap()
{
    QMutexLocker _(&m_mutex);
    return m_objMap;
}

int NetService::registerReadProcesser(int id, std::function<void (const QByteArray &)> cb)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id)) return -1;
    m_objMap[id]->obj->registerReadProcesser(cb);
    return 0;
}

int NetService::start(int id)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id)) return -1;
    return m_objMap[id]->obj->start();
}

int NetService::stop(int id)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id)) return -1;
    m_objMap[id]->obj->stop();
    return 0;
}

int NetService::send(int id, const QByteArray &data)
{
    QMutexLocker _(&m_mutex);
    if (!m_objMap.contains(id)) return -1;
    m_objMap[id]->obj->send(data);
    return 0;
}
