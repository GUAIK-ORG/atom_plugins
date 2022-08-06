#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QObject>
#include <QMap>
#include <QSharedPointer>
#include <QMutex>

#include "session.h"
#include "../netbase.h"

class TCPServer: public QTcpServer, public NetBase
{
    Q_OBJECT
public:
    TCPServer(quint16 port, QObject* parent = nullptr);

private:
    bool m_isRunning;
    quint16 m_port;

    QMutex m_sessMutex;
    QMap<int, Session*> m_sessions;
    QMutex m_readProcesserMutex;
    QVector<std::function<void(const QByteArray&)>> m_readProcessers;

protected:
    void incomingConnection(qintptr socketDescriptor) override;
    void registerReadProcesser(std::function<void(const QByteArray&)>cb) override;
    int start() override;
    void stop() override;
    void send(const QByteArray &data) override;
    void free() override;

public slots:
    void onDisconnected(int fd);
    void onReadyRead(int fd, const QByteArray& data);
};

#endif // TCPSERVER_H
