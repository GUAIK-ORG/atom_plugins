#ifndef ATOMPLUGIN_H
#define ATOMPLUGIN_H

#include "atomplugin_global.h"
#include "iplugin.h"
#include "icontext.h"

class ATOMPLUGIN_EXPORT ATOMPlugin: public IPlugin
{
public:
    ATOMPlugin();

protected:
    /** 插件加载事件
     * @brief onLoad
     * @param ctx 上下文对象
     * @return 成功:0 失败:-1
     */
    int onLoad(IContext* ctx) override;

    /** 插件初始化事件
     * @brief onInit
     * @return 成功:0 失败:-1
     */
    int onInit() override;

    /** 插件卸载事件
     * @brief onUnload
     */
    void onUnload() override;
private:
    IContext* m_ctx;
};

extern "C" {
    ATOMPLUGIN_EXPORT IPlugin* getInstance();
}

#endif // ATOMPLUGIN_H
