#ifndef INETSERVICE_H
#define INETSERVICE_H

#include <QByteArray>
#include <functional>
#include <QSharedPointer>
#include "netbase.h"

// 网络对象类型
typedef enum _NET_OBJECT_TYPE {
    TCP_SERVER,     // TCP服务端
    TCP_CLIENT,     // TCP客户端
} NET_OBJECT_TYPE;

// 网络对象
struct NetObject {
public:
    NetObject(QSharedPointer<NetBase> obj, NET_OBJECT_TYPE type) {
        this->obj = obj;
        this->type = type;
    }
    NET_OBJECT_TYPE type;
    QSharedPointer<NetBase> obj;
};

// 定义存储网络对象的MAP
typedef enum _TCP_CONNECT_STATE {
    CONNECTED,          // 连接
    UNCONNECTED,        // 未连接
} TCP_CONNECT_STATE;

typedef QMap<int, QSharedPointer<NetObject>> NET_OBJ_MAP;

class INetService {
public:
    /**
     * @brief 创建TCP服务端实例
     * @param port 本地监听端口
     * @return id:int 实例id <0(error)
     */
    virtual int newTCPServer(quint16 port) = 0;

    /**
     * @brief 创建TCP客户端实例
     * @param remoteIp 远程IP地址
     * @param remotePort 远程端口
     * @return ud:int 实例id <0(error)
     */
    virtual int newTCPClient(QString remoteIp, quint16 remotePort) = 0;

    /**
     * @brief 开启TCP客户端断线重连功能
     * @param id 实例id
     * @return errCode:int 错误码 0(success) -1(error)
     */
    virtual int enableTCPClientReconnect(int id) = 0;

    /**
     * @brief 注册TCP客户端（状态）处理者
     * @param id 实例id
     * @param cb 处理者回调函数
     * @return errCode:int 错误码 0(success) -1(error)
     */
    virtual int registerTCPClientStateProcesser(int id, std::function<void(TCP_CONNECT_STATE)>cb) = 0;

    /**
     * @brief 为TCP客户端绑定一个标签
     * @param id 实例id
     * @param tag 标签
     * @return errCode:int 错误码 0(success) -1(error)
     */
    virtual int bindTCPClientTag(int id, QString tag) = 0;

    /**
     * @brief 获取TCP客户端标签
     * @param id 实例id
     * @return tag:string ""(error)
     */
    virtual QString getTCPClientTag(int id) = 0;

    /**
     * @brief 获取网络对象MAP
     * @return netObjMap:map
     */
    virtual NET_OBJ_MAP getObjMap() = 0;

    /**
     * @brief 注册（读）处理者
     * @param id 实例id
     * @param cb 处理者回调函数
     * @return errCode:int 错误码 0(success) -1(error)
     */
    virtual int registerReadProcesser(int id, std::function<void(const QByteArray&)>cb) = 0;

    /**
     * @brief 启动实例
     * @param id 实例id
     * @return errCode:int 错误码 0(success) -1(error)
     */
    virtual int start(int id) = 0;

    /**
     * @brief 停止实例
     * @param id 实例id
     * @return errCode:int 错误码 0(success) -1(error)
     */
    virtual int stop(int id) = 0;

    /**
     * @brief 发送消息（服务端广播数据）
     * @param id 实例id
     * @param data 消息内容
     * @return errCode:int 错误码 0(success) -1(error)
     */
    virtual int send(int id, const QByteArray& data) = 0;
};

#endif // INETSERVICE_H
