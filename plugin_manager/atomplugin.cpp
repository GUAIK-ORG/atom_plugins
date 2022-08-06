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
    aDebug() << "onInit Debug";
    IWindowManager *winManager;
    if (0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER, (void**)&winManager)) {
        winManager->registerWidget(m_ctx, "plugin_manager", new MainWidget(m_ctx));
    }
    return 0;
}

void ATOMPlugin::onUnload()
{
    aDebug() << "onUnload Debug";
}

IPlugin* getInstance()
{
    return new ATOMPlugin();
}
