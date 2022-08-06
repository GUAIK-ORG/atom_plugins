#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include "icontext.h"
#include "imessage.h"
#include <QHBoxLayout>
#include <QMap>
#include <QSharedPointer>
#include "ievent.h"

class NetState: public QWidget {
public:
    NetState(QWidget *parent = nullptr) {
        Q_UNUSED(parent)
        QHBoxLayout* hLay = new QHBoxLayout();
        m_state = new QLabel();
        m_state->setFixedSize(15, 15);
        setState(false);
        m_tag = new QLabel();
        m_tag->setFixedHeight(15);
        hLay->setMargin(0);
        hLay->addWidget(m_tag);
        hLay->addWidget(m_state);
        this->setLayout(hLay);
    }

    void setState(bool state) {
        if (state) {
            m_state->setStyleSheet("background-color: #00ff00");
        } else {
            m_state->setStyleSheet("background-color: #ff0000");
        }
    }

    void setTag(QString text) { this->m_tag->setText(text); }

private:
    QLabel* m_state;
    QLabel* m_tag;
};

class MainWidget : public QWidget, public IMessageHandler, public IEventHandler
{
    Q_OBJECT
public:
    explicit MainWidget(IContext* ctx, QWidget *parent = nullptr);
    ~MainWidget();

private:
    IContext* m_ctx;
    QLabel* m_time;
    QTimer* m_timer;
    QHBoxLayout* m_netLay;
    QMap<int, QSharedPointer<NetState>> m_netStates;
    EVENT_OBJ* m_switchWidgetEvent;

protected:
    void onMessage(QString id, void *pArg) override;
    void onEvent(Event *e) override;

signals:

public slots:
    void onTimeOut();
};

#endif // MAINWIDGET_H
