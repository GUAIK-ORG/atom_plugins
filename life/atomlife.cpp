/**
 * 请勿使用插件管理器（iplugin）和窗体管理器(iwindow)，这两个管理器会判断组件类型，
 * 生命周期组件token和id为空，无法使用这两个管理器
 */


#include "atomlife.h"
#include <QDebug>
#include "iwindow.h"
#include "ilog.h"
#include "istorage.h"

ATOMLife::ATOMLife()
{
}

void ATOMLife::onBeforeLoadPlugin(IContext *ctx)
{
    Log::getInstance().init(ctx);
    IStorageManager* storage;
    if (0 == ctx->query(QUERY_TYPE::STORAGE_MANAGER, (void**)&storage)) {
        aInfo() << "==============================";
        aInfo() << "storage:";
        QMapIterator<QString, QString> i(storage->data());
        while (i.hasNext()) {
            i.next();
            aInfo() << "key:" << i.key() << " value:" << i.value();
        }
        aInfo() << "==============================";
    }
    aInfo() << "onBeforeLoadPlugin";
}

void ATOMLife::onAfterLoadPlugin(IContext *ctx)
{
    Q_UNUSED(ctx)
    aInfo() << "onAfterLoadPlugin";
}

void ATOMLife::onBeforeInitPlugin(IContext *ctx)
{
    Q_UNUSED(ctx)
    aInfo() << "onBeforeInitPlugin";
}

void ATOMLife::onAfterInitPlugin(IContext *ctx)
{
    Q_UNUSED(ctx)
    aInfo() << "onAfterInitPlugin";
}

void ATOMLife::onBeforeShow(IContext *ctx)
{
    Q_UNUSED(ctx)
    aInfo() << "onBeforeShow";
}

void ATOMLife::onAfterShow(IContext *ctx)
{
    Q_UNUSED(ctx)
    aInfo() << "onAfterShow";
}

void ATOMLife::onBeforeFree(IContext *ctx)
{
    Q_UNUSED(ctx)
    aInfo() << "onBeforeFree";
}

/**
 * @brief GKFLife::onAfterFree
 * 请不要在这个函数中调用任何管理器，此时除了日志管理器未释放
 * 其他所有管理器均已释放，在此处使用管理器可导致程序异常
 */
void ATOMLife::onAfterFree()
{
    aInfo() << "onAfterFree";
}



ILife* getInstance()
{
    return new ATOMLife();
}
