#include "mainwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QThread>
#include "iwindow.h"
#include "ilog.h"
#include "../net/inetservice.h"
#include "iplugin.h"

MainWidget::MainWidget(IContext* ctx, QWidget *parent)
    : QWidget(parent)
    , m_ctx(ctx)
{
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor("#132031"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);


    IMessageManager* msgManager;
    if (0 == m_ctx->query(QUERY_TYPE::MESSAGE_MANAGER, (void**)&msgManager)) {
        msgManager->registerMessageHandler("test-msg", this);
    }
    IMQMessageManager* mq;
    if (0 == m_ctx->query(QUERY_TYPE::MQ_MANAGER, (void**)&mq)) {
        aDebug() << "registerMessageHandler success";
        mq->registerMessageHandler("test-mq", this);
    }
    IEventManager* eventManager;
    if (0 == m_ctx->query(QUERY_TYPE::EVENT_MANAGER, (void**)&eventManager)) {
        m_switchWidgetEvent = new EVENT_OBJ(10, this);
        eventManager->registerEventHandler(EVENT_ID::SWITCH_WIDGET, m_switchWidgetEvent);
    }

    QHBoxLayout* mainLayout = new QHBoxLayout();

    QPushButton* sendMsgbtn = new QPushButton("发送消息测试");
    connect(sendMsgbtn, &QPushButton::clicked, this, [=](){
        for(int i=0; i< 100; i++) {
            int *a = new int();
            *a = i;
            IMessageManager* msgManager;
            if (0 == m_ctx->query(QUERY_TYPE::MESSAGE_MANAGER, (void**)&msgManager)) {
                msgManager->sendMessage("test-msg", (void*)a);
            }
            delete a;
        }
    });

    QPushButton* switchStatusbarBtn = new QPushButton("显示/隐藏 状态栏");
    connect(switchStatusbarBtn, &QPushButton::clicked, this, [=](){
        IWindowManager* winManager;
        if (0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER, (void**)&winManager)) {
            if(m_showStatusbar) {
                m_showStatusbar = false;
                winManager->hideStatusbar();
            } else {
                m_showStatusbar = true;
                winManager->showStatusbar();
            }
        }
    });

    QPushButton* MQSendBtn = new QPushButton("消息队列测试");
    connect(MQSendBtn, &QPushButton::clicked, this, [=](){
        IMQMessageManager* mq;
        if (0 == m_ctx->query(QUERY_TYPE::MQ_MANAGER, (void**)&mq)) {
            aDebug() << "mq->sendMessage success";
            mq->sendMessage("test-mq", QString("hello mq").toLatin1());
        }
    });

    QPushButton* createServerBtn = new QPushButton("创建服务端");
    connect(createServerBtn, &QPushButton::clicked, this, [=](){
        IPluginManager* pluginManager;
        if (0 == m_ctx->query(QUERY_TYPE::PLUGIN_MANAGER, (void**)&pluginManager)) {
            INetService* net = (INetService*)pluginManager->interfaceObj(m_ctx, "net");
            if (net) {
                int id = net->newTCPServer(9720);
                net->registerReadProcesser(id, [=](const QByteArray& data){
                    aDebug() << QString(data);
                    net->send(id, QString("hello client").toLatin1());
                });
                net->start(id);
                aDebug() << "create server id:" << id;
            }
        }
    });

    QPushButton* createClientBtn = new QPushButton("创建客户端");
    connect(createClientBtn, &QPushButton::clicked, this, [=](){
        IPluginManager* pluginManager;
        if (0 == m_ctx->query(QUERY_TYPE::PLUGIN_MANAGER, (void**)&pluginManager)) {
            INetService* net = (INetService*)pluginManager->interfaceObj(m_ctx, "net");
            if (net) {
                int id = net->newTCPClient("localhost", 9720);
                net->registerReadProcesser(id, [=](const QByteArray& data){
                    aDebug() << QString(data);
                });
                net->bindTCPClientTag(id, QString("cli-%1").arg(id));
                net->enableTCPClientReconnect(id);
                net->start(id);
                net->send(id, QString("hello server").toLatin1());
            }
        }
    });


    mainLayout->addStretch();
    mainLayout->addWidget(sendMsgbtn);
    mainLayout->addWidget(switchStatusbarBtn);
    mainLayout->addWidget(MQSendBtn);
    mainLayout->addWidget(createServerBtn);
    mainLayout->addWidget(createClientBtn);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

MainWidget::~MainWidget()
{
    IEventManager* eventManager;
    if (0 == m_ctx->query(QUERY_TYPE::EVENT_MANAGER, (void**)&eventManager)) {
        eventManager->unregisterEventHandler(EVENT_ID::SWITCH_WIDGET, m_switchWidgetEvent);
        delete m_switchWidgetEvent;
    }
}

void MainWidget::onMessage(QString id, void *pArg)
{
    int msg = *static_cast<int*>(pArg);
    aDebug() << msg;
}

void MainWidget::onMessage(QString id, const QByteArray &data)
{
    aDebug() << id;
    aDebug() << QString(data);
}

void MainWidget::onEvent(Event *e)
{
    if (e->id() == EVENT_ID::SWITCH_WIDGET) {
        aDebug() << "dbg EVENT_ID::SWITCH_WIDGET : " << static_cast<SWITCH_WIDGET_EVENT*>(e->arg())->pluginId;
        e->next();
    }
}
