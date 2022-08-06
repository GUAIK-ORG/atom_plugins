#include "mainwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <ilog.h>
#include <QThread>
#include <QDateTime>
#include <iplugin.h>
#include "../net/inetservice.h"

MainWidget::MainWidget(IContext* ctx, QWidget *parent)
    : QWidget(parent)
    , m_ctx(ctx)
{
    IEventManager* eventManager;
    if (0 == m_ctx->query(QUERY_TYPE::EVENT_MANAGER, (void**)&eventManager)) {
        m_switchWidgetEvent = new EVENT_OBJ(5, this);
        eventManager->registerEventHandler(EVENT_ID::SWITCH_WIDGET, m_switchWidgetEvent);
    }


    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color:#000000;color:#ffffff");
    this->setFixedHeight(30);
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    m_time = new QLabel();

    QWidget* stateWid = new QWidget();
    m_netLay = new QHBoxLayout();
    m_netLay->setMargin(0);
    stateWid->setLayout(m_netLay);

    mainLayout->addWidget(stateWid);
    mainLayout->addStretch();
    mainLayout->addWidget(m_time);
    mainLayout->addSpacing(20);

    this->setLayout(mainLayout);

    m_timer = new QTimer();
    m_timer->setInterval(1000);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    m_timer->start();
}

MainWidget::~MainWidget() {
    IEventManager* eventManager;
    if (0 == m_ctx->query(QUERY_TYPE::EVENT_MANAGER, (void**)&eventManager)) {
        eventManager->unregisterEventHandler(EVENT_ID::SWITCH_WIDGET, m_switchWidgetEvent);
        delete m_switchWidgetEvent;
    }
}

void MainWidget::onMessage(QString id, void *pArg)
{

}

void MainWidget::onEvent(Event *e)
{
    if (e->id() == EVENT_ID::SWITCH_WIDGET) {
        aDebug() << "statusbar EVENT_ID::SWITCH_WIDGET : " << static_cast<SWITCH_WIDGET_EVENT*>(e->arg())->pluginId;
        e->next();
    }
}

void MainWidget::onTimeOut()
{
    QDateTime curDateTime = QDateTime::currentDateTime();
    m_time->setText(curDateTime.toString("yyyy-MM-dd hh:mm:ss"));

    IPluginManager* pluginManager = nullptr;
    if (0 == m_ctx->query(QUERY_TYPE::PLUGIN_MANAGER, (void**)&pluginManager)) {
        INetService* netService = static_cast<INetService*>(pluginManager->interfaceObj(m_ctx, "net"));
        if (netService) {
            NET_OBJ_MAP objs = netService->getObjMap();
            for (NET_OBJ_MAP::iterator it=objs.begin(); it!=objs.end(); it++) {
                if (it.value()->type != NET_OBJECT_TYPE::TCP_CLIENT) continue;
                if (!m_netStates.contains(it.key())) {
                    m_netStates[it.key()] = QSharedPointer<NetState>(new NetState());
                    m_netLay->addSpacing(5);
                    m_netLay->addWidget(m_netStates[it.key()].data());
                    int key = it.key();
                    netService->registerTCPClientStateProcesser(key, [=](TCP_CONNECT_STATE state){
                        switch (state) {
                        case TCP_CONNECT_STATE::CONNECTED:
                            m_netStates[key]->setState(true);
                            break;
                        case TCP_CONNECT_STATE::UNCONNECTED:
                            m_netStates[key]->setState(false);
                            break;
                        }

                    });
                }
                m_netStates[it.key()]->setTag(netService->getTCPClientTag(it.key()));
            }

        }
    }
}

