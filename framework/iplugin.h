/**
 * @file iplugin.h
 * @author Rick (rick@guaik.io)
 * @brief 插件管理器
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IPLUGIN_H
#define IPLUGIN_H
#include "icontext.h"
#include <QString>

class IPluginManager
{
public:
    /**
     * @brief 注册接口对象（仅服务可用）
     * 
     * @param ctx 上下文对象
     * @param interfaceObj 接口对象
     * @return int 成功:0
     */
    virtual int registerInterfaceObj(IContext *ctx, void *interfaceObj) = 0;

    /**
     * @brief 获取接口对象
     * 
     * @param ctx 上下文对象
     * @param id 插件ID
     * @return void* 接口对象
     */
    virtual void *interfaceObj(IContext *ctx, QString id) = 0;

    /**
     * @brief 获取所有插件的键
     * 
     * @return QStringList 
     */
    virtual QStringList pluginKeys() = 0;

    /**
     * @brief 获取所有服务的键
     * 
     * @return QStringList 
     */
    virtual QStringList serviceKeys() = 0;

    /**
     * @brief 获取所有窗体的键
     * 
     * @return QStringList 
     */
    virtual QStringList windowKeys() = 0;
};

class IPlugin
{
public:
    /**
     * @brief 插件加载回调函数
     * 
     * @param ctx 上下文对象
     * @return int 加载成功:0
     */
    virtual int onLoad(IContext *ctx) = 0;

    /**
     * @brief 插件初始化回调函数
     * 
     * @return int 初始化成功:0
     */
    virtual int onInit() = 0;

    /**
     * @brief 插件卸载回调函数
     * 
     */
    virtual void onUnload() = 0;
};

#endif // IPLUGIN_H
