#ifndef NETSERVICE_H
#define NETSERVICE_H
#include <QObject>
#include <QMap>
#include <QMutex>
#include <qbasicatomic.h>
#include "inetservice.h"


class NetService : public QObject, public INetService
{
    Q_OBJECT
public:
    explicit NetService(QObject *parent = nullptr);
    void free();

    int newTCPServer(quint16 port) override;
    int newTCPClient(QString remoteIp, quint16 remotePort) override;
    int enableTCPClientReconnect(int id) override;
    int registerTCPClientStateProcesser(int id, std::function<void (TCP_CONNECT_STATE)> cb) override;
    int bindTCPClientTag(int id, QString tag) override;
    QString getTCPClientTag(int id) override;
    NET_OBJ_MAP getObjMap() override;

    int registerReadProcesser(int id, std::function<void (const QByteArray &)> cb) override;
    int start(int id) override;
    int stop(int id) override;
    int send(int id, const QByteArray &data) override;
signals:

private:
    QBasicAtomicInt m_idGenerator;
    NET_OBJ_MAP m_objMap;
    QMutex m_mutex;

};

#endif // NETSERVICE_H
