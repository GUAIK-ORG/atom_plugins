/**
 * @file ilife.h
 * @author Rick (rick@guaik.io)
 * @brief 生命周期回调函数
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ILIFE_H
#define ILIFE_H
#include "icontext.h"

class ILife
{
public:
    /**
     * @brief 加载插件前
     * 
     * @param ctx 
     */
    virtual void onBeforeLoadPlugin(IContext *ctx) = 0;

    /**
     * @brief 加载插件后
     * 
     * @param ctx 
     */
    virtual void onAfterLoadPlugin(IContext *ctx) = 0;

    /**
     * @brief 初始化插件前
     * 
     * @param ctx 
     */
    virtual void onBeforeInitPlugin(IContext *ctx) = 0;

    /**
     * @brief 初始化插件后
     * 
     * @param ctx 
     */
    virtual void onAfterInitPlugin(IContext *ctx) = 0;

    /**
     * @brief 框架显示前
     * 
     * @param ctx 
     */
    virtual void onBeforeShow(IContext *ctx) = 0;

    /**
     * @brief 框架显示后
     * 
     * @param ctx 
     */
    virtual void onAfterShow(IContext *ctx) = 0;

    /**
     * @brief 资源释放前
     * 
     * @param ctx 
     */
    virtual void onBeforeFree(IContext *ctx) = 0;

    /**
     * @brief 资源释放后
     * 
     */
    virtual void onAfterFree() = 0;
};

#endif // ILIFE_H
