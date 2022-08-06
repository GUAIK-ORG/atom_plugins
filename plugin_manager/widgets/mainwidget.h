#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "icontext.h"
#include "createplugin.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(IContext* ctx, QWidget *parent = nullptr);
    ~MainWidget();

private:
    IContext *m_ctx;
    CreatePlugin *m_createPlugin;

signals:

public slots:
};

#endif // MAINWIDGET_H
