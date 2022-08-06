#ifndef NETBASE_H
#define NETBASE_H

#include <functional>
#include <QByteArray>

class NetBase {
public:
    virtual void registerReadProcesser(std::function<void(const QByteArray&)>cb) = 0;
    virtual int start() = 0;
    virtual void stop() = 0;
    virtual void send(const QByteArray& data) = 0;
    virtual void free() = 0;
};

#endif // NETBASE_H
