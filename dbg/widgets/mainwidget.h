#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "icontext.h"
#include "imessage.h"
#include "imq.h"
#include "ievent.h"

class MainWidget : public QWidget, public IMessageHandler, public IMQMessageHandler, public IEventHandler
{
    Q_OBJECT
public:
    explicit MainWidget(IContext* ctx, QWidget *parent = nullptr);
    ~MainWidget();

private:
    IContext* m_ctx;
    bool m_showStatusbar = true;
    EVENT_OBJ* m_switchWidgetEvent;

protected:
    void onMessage(QString id, void *pArg) override;
    void onMessage(QString id, const QByteArray &data) override;
    void onEvent(Event *e) override;

signals:

public slots:
};

#endif // MAINWIDGET_H
