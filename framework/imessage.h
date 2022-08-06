/**
 * @file imessage.h
 * @author Rick (rick@guaik.io)
 * @brief 消息管理器
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IMESSAGE_H
#define IMESSAGE_H
#include <QString>

/**
 * @brief 消息处理器
 * 
 */
class IMessageHandler
{
public:
    /**
     * @brief 消息回调函数
     * 
     * @param id 消息ID
     * @param pArg 消息参数
     */
    virtual void onMessage(QString id, void *pArg) = 0;
};

class IMessageManager
{
public:
    /**
     * @brief 注册消息处理器
     * 
     * @param id 消息ID
     * @param messageHandler 消息处理器对象 
     */
    virtual void registerMessageHandler(QString id, IMessageHandler *messageHandler) = 0;

    /**
     * @brief 注销消息处理器
     * 
     * @param id 消息ID
     * @param messageHandler 消息处理器对象
     */
    virtual void unregisterMessageHandler(QString id, IMessageHandler *messageHandler) = 0;

    /**
     * @brief 发送一条消息
     * 
     * @param id 消息ID
     * @param pArg 消息参数
     */
    virtual void sendMessage(QString id, void *pArg) = 0;
};

#endif // IMESSAGEHAND
