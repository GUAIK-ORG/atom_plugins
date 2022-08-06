#include "atomplugin.h"
#include <QDebug>
#include "iwindow.h"
#include "iplugin.h"
#include "tcp/tcpserver.h"
#include "ilog.h"
#include "netservice.h"
#include <QString>
#include "inetservice.h"

ATOMPlugin::ATOMPlugin()
    : m_ctx(nullptr)
    , m_netService(nullptr)
{}

int ATOMPlugin::onLoad(IContext *ctx)
{
    m_ctx = ctx;
    Log::getInstance().init(ctx);
    IPluginManager *pluginManager;
    if (0 == m_ctx->query(QUERY_TYPE::PLUGIN_MANAGER, (void**)&pluginManager)) {
        m_netService = dynamic_cast<INetService*>(new NetService);
        pluginManager->registerInterfaceObj(m_ctx, m_netService);
    }
    return 0;
}

int ATOMPlugin::onInit()
{
    aDebug() << "onInit Net";
    return 0;
}

void ATOMPlugin::onUnload()
{
    aDebug() << "onUnload Net";
    if (nullptr != m_netService) {
        NetService* s = dynamic_cast<NetService*>(m_netService);
        if (s) {
            s->free();
            delete s;
            m_netService = nullptr;
        }
    }
}

IPlugin* getInstance()
{
    return new ATOMPlugin();
}
