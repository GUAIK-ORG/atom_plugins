#ifndef CREATEPLUGIN_H
#define CREATEPLUGIN_H

#include <QWidget>
#include <QObject>
#include "icontext.h"
#include "iplugin.h"

namespace Ui {
class CreatePlugin;
}

class CreatePlugin : public QWidget
{
    Q_OBJECT

public:
    explicit CreatePlugin(IContext* ctx, QWidget *parent = nullptr);
    ~CreatePlugin();

private slots:
    void on_type_cbox_currentIndexChanged(int index);

    void on_gen_plugin_btn_clicked();

private:
    Ui::CreatePlugin *ui;
    IPluginManager *m_pluginManager;
    bool genDir();
    bool genYml();
    bool genPro();
    bool copyFiles();
};

#endif // CREATEPLUGIN_H
