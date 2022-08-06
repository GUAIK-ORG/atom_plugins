#ifndef ATOMLIFE_H
#define ATOMLIFE_H

#include "atomlife_global.h"
#include "ilife.h"
#include "ilog.h"
#include "icontext.h"

class ATOMLIFE_EXPORT ATOMLife: public ILife
{
public:
    ATOMLife();

protected:
    void onBeforeLoadPlugin(IContext *ctx) override;
    void onAfterLoadPlugin(IContext *ctx) override;

    void onBeforeInitPlugin(IContext *ctx) override;
    void onAfterInitPlugin(IContext *ctx) override;

    void onBeforeShow(IContext *ctx) override;
    void onAfterShow(IContext *ctx) override;

    void onBeforeFree(IContext *ctx) override;
    void onAfterFree() override;
};

extern "C" {
    ATOMLIFE_EXPORT ILife* getInstance();
}

#endif // ATOMLIFE_H
