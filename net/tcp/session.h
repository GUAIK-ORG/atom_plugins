#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include <QThread>
#include <QByteArray>
#include "tcpsocket.h"

class Session : public QThread
{
    Q_OBJECT
public:
    explicit Session(qintptr fd, QObject *parent = nullptr);
    void send(const QByteArray& data);

private:
    qintptr m_fd;
    TcpSocket* m_socket;

protected:
    void run() override;

public slots:
    void onReadyRead();
    void onDisconnected();

signals:
    void readyRead(int fd, const QByteArray& data);
    void disconnected(int fd);
    void sendData(const QByteArray& data);
};

#endif // SESSION_H
