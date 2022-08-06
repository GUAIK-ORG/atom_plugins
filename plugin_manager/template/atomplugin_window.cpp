#include "atomplugin.h"
#include "ilog.h"
#include "widgets/mainwidget.h"
#include "iwindow.h"

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
    IWindowManager *winManager;
    if(0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER,(void**)&winManager)) {
        aDebug() << "registerWidget {{id}} state: " << winManager->registerWidget(m_ctx, "{{id}}", new MainWidget(m_ctx));
    }

    return 0;
}

void ATOMPlugin::onUnload()
{

}

IPlugin* getInstance()
{
    return new ATOMPlugin();
}
