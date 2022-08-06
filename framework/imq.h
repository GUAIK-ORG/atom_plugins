/**
 * @file imq.h
 * @author Rick (rick@guaik.io)
 * @brief 消息队列管理器
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __IMQ_H__
#define __IMQ_H___

#include <QByteArray>
#include <QString>

/**
 * @brief 消息队列处理器
 * 
 */
class IMQMessageHandler
{
public:
    /**
     * @brief 消息队列回调函数
     * 
     * @param topic 主题
     * @param data 数据
     */
    virtual void onMessage(QString topic, const QByteArray &data) = 0;
};

class IMQMessageManager
{
public:
    /**
     * @brief 注册消息队列处理器
     * 
     * @param topic 主题
     * @param messageHandler 消息队列处理器对象
     */
    virtual void registerMessageHandler(QString topic, IMQMessageHandler *messageHandler) = 0;

    /**
     * @brief 注销消息队列处理器
     * 
     * @param topic 主题
     * @param messageHandler 消息队列处理器对象 
     */
    virtual void unregisterMessageHandler(QString topic, IMQMessageHandler *messageHandler) = 0;

    /**
     * @brief 发送消息
     * 
     * @param topic 主题
     * @param data 数据
     */
    virtual void sendMessage(QString topic, const QByteArray &data) = 0;
};

#endif