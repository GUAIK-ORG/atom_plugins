#ifndef ATOMPLUGIN_H
#define ATOMPLUGIN_H

#include "atomplugin_global.h"
#include "iplugin.h"
#include "icontext.h"
#include "coordsys.h"

class ATOMPLUGIN_EXPORT ATOMPlugin: public IPlugin
{
public:
    ATOMPlugin();

protected:
    int onLoad(IContext* ctx) override;
    int onInit() override;
    void onUnload() override;
private:
    IContext* m_ctx;
    CoordSys* m_coordSys;
};

extern "C" {
    ATOMPLUGIN_EXPORT IPlugin* getInstance();
}

#endif // ATOMPLUGIN_H
