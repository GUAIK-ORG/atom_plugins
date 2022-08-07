/**
 * @file iwindow.h
 * @author Rick (rick@guaik.io)
 * @brief 窗体管理器
 * @version 0.1
 * @date 2022-08-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IWINDOW_H
#define IWINDOW_H
#include "icontext.h"
#include <QString>
#include <QWidget>

class IWindowManager
{
public:
    /**
     * @brief 显示状态栏
     * 
     */
    virtual void showStatusbar() = 0;

    /**
     * @brief 隐藏状态栏
     * 
     */
    virtual void hideStatusbar() = 0;

    /**
     * @brief 显示标题栏
     * 
     */
    virtual void showTitlebar() = 0;

    /**
     * @brief 隐藏标题栏
     * 
     */
    virtual void hideTitlebar() = 0;

    /**
     * @brief 注册窗体对象
     * 
     * @param ctx 上下文对象
     * @param id 注册窗体对象ID（插件ID）
     * @param widget 窗体对象
     * @return int 成功:0
     */
    virtual int registerWidget(IContext *ctx, QString id, QWidget *widget) = 0;

    /**
     * @brief 弹窗显示窗体
     * 
     * @param ctx 上下文对象
     * @param widgetId 窗体ID
     */
    virtual void popupWidget(IContext *ctx, QString widgetId) = 0;

    /**
     * @brief 切换标题栏
     * 
     * @param ctx 上下文对象
     * @param titlebarId 标题栏插件ID
     */
    virtual void switchTitlebar(IContext *ctx, QString titlebarId) = 0;

    /**
     * @brief 切换状态栏
     * 
     * @param ctx 上下文对象
     * @param statusbarId 状态栏插件ID
     */
    virtual void switchStatusbar(IContext *ctx, QString statusbarId) = 0;

    /**
     * @brief 最大化框架窗体
     * 
     */
    virtual void showMaximize() = 0;

    /**
     * @brief 最小化框架窗体
     * 
     */
    virtual void showMinimize() = 0;

    /**
     * @brief 默认显示框架窗体（窗体大小在框架配置文件中定义）
     * 
     */
    virtual void showNormal() = 0;

    /**
     * @brief 全屏显示框架窗体
     * 
     */
    virtual void showFullScreen() = 0;

    /**
     * @brief 显示框架窗体
     * 
     */
    virtual void show() = 0;

    /**
     * @brief 隐藏框架窗体
     * 
     */
    virtual void hide() = 0;

    /**
     * @brief 当前框架窗体是否最大化
     * 
     * @return true 
     * @return false 
     */
    virtual bool isMaximize() = 0;

    /**
     * @brief 当前框架窗体是否最小化
     * 
     * @return true 
     * @return false 
     */
    virtual bool isMinimize() = 0;

    /**
     * @brief 当前框架窗体是否全屏
     * 
     * @return true 
     * @return false 
     */
    virtual bool isFullScreen() = 0;

    virtual QWidget *mainView() = 0;
};

#endif