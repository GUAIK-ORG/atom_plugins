#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QVector>
#include <QMutex>
#include <QTimer>
#include "../netbase.h"
#include "../inetservice.h"


class TcpClient : public QObject, public NetBase
{
    Q_OBJECT
public:
    explicit TcpClient(QString remoteIp, quint16 remotePort, QObject *parent = nullptr);
    void enableReconnect() { m_isNeedReconnect = true; }
    void registerStateProcesser(std::function<void(TCP_CONNECT_STATE)>cb);
    void bindTag(QString tag) { m_tag = tag; }
    QString getTag() { return m_tag; }

public slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onCheckState();

protected:
    void registerReadProcesser(std::function<void (const QByteArray &)> cb) override;
    int start() override;
    void stop() override;
    void send(const QByteArray &data) override;
    void free() override;

private:
    bool m_isRunning;
    QString m_remoteIp;
    quint16 m_remotePort;
    QTcpSocket m_socket;
    QMutex m_readProcesserMutex;
    QVector<std::function<void(const QByteArray&)>> m_readProcessers;
    QMutex m_stateProcesserMutex;
    QVector<std::function<void(TCP_CONNECT_STATE)>> m_stateProcessers;
    QTimer m_checkStateTimer;
    bool m_isNeedReconnect;
    QString m_tag;

    void callStateProcessers(TCP_CONNECT_STATE state);
};

#endif // TCPCLIENT_H
