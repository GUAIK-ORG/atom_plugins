#include "atomplugin.h"
#include <QDebug>
#include "widgets/mainwidget.h"
#include "iwindow.h"
#include "ilog.h"

ATOMPlugin::ATOMPlugin()
{
}

int ATOMPlugin::onLoad(IContext *ctx)
{
    m_ctx = ctx;
    Log::getInstance().init(ctx);
    return 0;
}

int ATOMPlugin::onInit()
{
    aDebug() << "onInit Titlebar";
    IWindowManager *winManager;
    if(0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER,(void**)&winManager)) {
        aDebug() << "reg win ret:" << winManager->registerWidget(m_ctx, "titlebar", new MainWidget(m_ctx));
    }
    return 0;
}

void ATOMPlugin::onUnload()
{
    aDebug() << "onUnload Titlebar";
}

IPlugin* getInstance()
{
    return new ATOMPlugin();
}
