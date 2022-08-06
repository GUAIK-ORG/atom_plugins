#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "icontext.h"
#include "imessage.h"

class MainWidget : public QWidget, public IMessageHandler
{
    Q_OBJECT
public:
    explicit MainWidget(IContext* ctx, QWidget *parent = nullptr);

private:
    IContext* m_ctx;

protected:
    void onMessage(QString id, void *pArg) override;

signals:

public slots:
};

#endif // MAINWIDGET_H
