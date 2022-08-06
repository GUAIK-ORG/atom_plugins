#include "atomplugin.h"
#include <QDebug>
#include "iwindow.h"
#include "spectrum.h"
#include "ilog.h"

ATOMPlugin::ATOMPlugin()
    :m_coordSys(NULL)
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
    aDebug() << "onInit Chart";
    m_coordSys = new CoordSys();
    IWindowManager *winManager;
    if(0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER,(void**)&winManager)) {

        winManager->registerWidget(m_ctx, "chart", new Spectrum(m_coordSys));
    }
    return 0;
}

void ATOMPlugin::onUnload()
{
    aDebug() << "onUnload Chart";
    if (NULL != m_coordSys) {
        delete m_coordSys;
        m_coordSys = NULL;
    }
}

IPlugin* getInstance()
{
    return new ATOMPlugin();
}
