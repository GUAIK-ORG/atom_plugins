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
    virtual void showStatusbar() = 0;
    virtual void hideStatusbar() = 0;
    virtual void showTitlebar() = 0;
    virtual void hideTitlebar() = 0;
    virtual int registerWidget(IContext *ctx, QString id, QWidget *widget) = 0;
    virtual void popupWidget(IContext *ctx, QString widgetId) = 0;
    virtual void switchTitlebar(IContext *ctx, QString titlebarId) = 0;
    virtual void switchStatusbar(IContext *ctx, QString statusbarId) = 0;

    virtual void showMaximize() = 0;
    virtual void showMinimize() = 0;
    virtual void showNormal() = 0;
    virtual void showFullScreen() = 0;
    virtual void show() = 0;
    virtual void hide() = 0;

    virtual bool isMaximize() = 0;
    virtual bool isMinimize() = 0;
    virtual bool isFullScreen() = 0;

    virtual QWidget *mainView() = 0;
};

#endif