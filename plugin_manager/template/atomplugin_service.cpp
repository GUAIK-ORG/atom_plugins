#include "atomplugin.h"
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

    return 0;
}

void ATOMPlugin::onUnload()
{

}

IPlugin* getInstance()
{
    return new ATOMPlugin();
}
