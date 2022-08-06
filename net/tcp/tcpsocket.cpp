#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent) : QTcpSocket(parent)
{

}

void TcpSocket::onSendData(const QByteArray &data)
{
    this->write(data);
}
