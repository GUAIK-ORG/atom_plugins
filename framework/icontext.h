/**
 * @file icontext.h
 * @author Rick (rick@guaik.io)
 * @brief 上下文对象
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ICONTEXT_H
#define ICONTEXT_H

#include <QString>

typedef enum _QUERY_TYPE
{
    PLUGIN_MANAGER = 0x1000, // 插件管理器对象
    WINDOW_MANAGER,          // 窗口管理器对象
    MESSAGE_MANAGER,         // 消息管理器对象
    MQ_MANAGER,              // 消息队列管理器对象
    LOG_MANAGER,             // 日志管理器对象
    STORAGE_MANAGER,         // 存储管理器对象
    EVENT_MANAGER,           // 事件管理器对象
    FONT_MANAGER,            // 字体管理器对象
} QUERY_TYPE;

class IContext
{
public:
    /** 
     * @brief 查询管理器对象
     * 
     * @param type [IN] 需要获取管理器的类型
     * @param ptr  [OUT] 输出管理器对象指针
     * @return int 成功:0
     */
    virtual int query(QUERY_TYPE type, void **ptr) = 0;

    /**
     * @brief 获取当前插件token
     * 
     * @return const QString& token
     */
    virtual const QString &token() = 0;

    /**
     * @brief 获取当前插件id
     * 
     * @return const QString& id
     */
    virtual const QString &id() = 0;
};

#endif // ICONTEXT_H
