/**
 * @file ievent.h
 * @author Rick (rick@guaik.io)
 * @brief 事件对象
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IEVENT_H
#define IEVENT_H

#include <QString>

#define PLUGIN_EVENT_BASE 0x1000
#define WINDOW_EVENT_BASE 0x2000

/**
 * @brief 窗体切换事件
 * 
 */
typedef struct _SWITCH_WIDGET_EVENT
{
    QString pluginId;   // 插件ID
} SWITCH_WIDGET_EVENT;

typedef enum _EVENT_ID
{
    /* 窗体相关事件 */
    SWITCH_WIDGET = WINDOW_EVENT_BASE + 1  // 窗体切换事件ID
} EVENT_ID;

class Event
{
public:
    /**
     * @brief 构造一个新的事件对象
     * 
     * @param id 事件ID
     * @param pArg 事件参数
     */
    Event(EVENT_ID id, void *pArg)
    {
        m_id = id;
        m_bNext = true;
        m_pArg = pArg;
    }

    /**
     * @brief 将当前事件传递到下层处理器
     * 
     */
    void next() { m_bNext = true; }

    /**
     * @brief 停止事件的传递
     * 
     */
    void stop() { m_bNext = false; }
    EVENT_ID id() { return m_id; }
    bool isNext() { return m_bNext; }
    void *arg() { return m_pArg; }

private:
    EVENT_ID m_id;
    bool m_bNext;
    void *m_pArg;
};


/**
 * @brief 事件处理器
 * 
 */
class IEventHandler
{
public:
    /**
     * @brief 事件处理回调函数
     * 
     * @param e 事件
     */
    virtual void onEvent(Event *e) = 0;
};

class EVENT_OBJ
{
public:
    int weight;
    IEventHandler *handler;
    EVENT_OBJ() {}
    EVENT_OBJ(int w, IEventHandler *handler)
    {
        this->weight = w;
        this->handler = handler;
    }
};


/**
 * @brief 事件管理器
 * 
 */
class IEventManager
{
public:
    /**
     * @brief 注册事件处理器
     * 
     * @param id 事件ID
     * @param obj 事件对象
     */
    virtual void registerEventHandler(EVENT_ID id, EVENT_OBJ *obj) = 0;

    /**
     * @brief 注销事件处理器
     * 
     * @param id 事件ID
     * @param obj 事件对象
     */
    virtual void unregisterEventHandler(EVENT_ID id, EVENT_OBJ *obj) = 0;
};

#endif