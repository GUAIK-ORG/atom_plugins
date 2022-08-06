#include "createplugin.h"
#include "ui_createplugin.h"
#include <QStringList>
#include "../fa.h"
#include "icontext.h"
#include "ilog.h"
#include "ifont.h"
#include <QMap>
#include <QString>
#include <QStyledItemDelegate>
#include <QDir>
#include <QMessageBox>

CreatePlugin::CreatePlugin(IContext* ctx, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CreatePlugin)
{
    ui->setupUi(this);

    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor(255, 255, 255, 10));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    ui->name_edt->setPlaceholderText("名称");
    ui->id_edt->setPlaceholderText("ID（英文和下划线）");
    ui->version_edt->setPlaceholderText("版本号");
    ui->description_edt->setPlaceholderText("描述");
    ui->sort_weight_edt->setPlaceholderText("排序权重（数字）");
    ui->icon_color_edt->setPlaceholderText("图标颜色（#ffffff）");

    ui->type_cbox->addItem("服务");
    ui->type_cbox->addItem("窗体");

    ui->display_mode_cbox->addItem("内嵌");
    ui->display_mode_cbox->addItem("弹窗");

    QStyledItemDelegate *itemDelegate = new QStyledItemDelegate();
    ui->type_cbox->setItemDelegate(itemDelegate);
    ui->icon_cbox->setItemDelegate(itemDelegate);
    ui->display_mode_cbox->setItemDelegate(itemDelegate);

    IFontManager *fontManager;
    if (0 == ctx->query(QUERY_TYPE::FONT_MANAGER, (void**)&fontManager)) {
        QMap<QString, unsigned short>::iterator iter = Fa::icons.begin();
        while (iter != Fa::icons.end()) {
           ui->icon_cbox->addItem(fontManager->GetIcon(iter.value(), 32, QColor(255,255,255)), iter.key());
           iter++;
       }
    }

    if (0 == ctx->query(QUERY_TYPE::PLUGIN_MANAGER, (void**)&m_pluginManager)) {
        ui->dependent_list->addItems(m_pluginManager->serviceKeys());
    }
}

CreatePlugin::~CreatePlugin()
{
    delete ui;
}

void CreatePlugin::on_type_cbox_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->win_gbox->hide();
    } else if (index == 1) {
        ui->win_gbox->show();
    }
}


void CreatePlugin::on_gen_plugin_btn_clicked()
{
    if (ui->name_edt->text().isEmpty()) {
        aWarn() << "name is empty";
        QMessageBox::information(nullptr, "", "名称不能为空");
        return;
    }

    if (ui->id_edt->text().isEmpty()) {
        aWarn() << "id is empty";
        QMessageBox::information(nullptr, "", "ID不能为空");
        return;
    }

    if (ui->version_edt->text().isEmpty()) {
        aWarn() << "version is empty";
        QMessageBox::information(nullptr, "", "版本不能为空");
        return;
    }

    if (ui->description_edt->text().isEmpty()) {
        aWarn() << "description is empty";
        QMessageBox::information(nullptr, "", "描述不能为空");
        return;
    }

    if (ui->sort_weight_edt->text().isEmpty()) {
        aWarn() << "sort_weight is empty";
        QMessageBox::information(nullptr, "", "排序权重不能为空");
        return;
    }

    if (ui->icon_color_edt->text().isEmpty()) {
        aWarn() << "icon_color is empty";
        QMessageBox::information(nullptr, "", "图标颜色不能为空");
        return;
    }


    if(m_pluginManager->pluginKeys().contains(ui->id_edt->text())) {
        aWarn() << "plugin id exist!!!";
        return;
    }

    if (!genDir()) return;
    if (!genYml()) return;
    if (!genPro()) return;
    if (!copyFiles()) return;
    aInfo() << "plugin generation succeeded";
    QMessageBox::information(nullptr, "", "插件生成成功");
}

bool CreatePlugin::genDir()
{
    QString path = QString("%1/../plugins/%2")
            .arg(QCoreApplication::applicationDirPath())
            .arg(ui->id_edt->text());
    QDir dir(path);
    if(dir.exists()) {
        aWarn() << "dir exists";
        return false;
    }
    dir.setPath("");
    if (!dir.mkpath(path)) {
        aWarn() << "mkpath failed";
        return false;
    }

    if (ui->type_cbox->currentIndex() == 1) {
        dir.setPath(path);
        if (!dir.mkdir("widgets")) {
            aWarn() << "mkpath failed";
            return false;
        }
    }
    return true;
}

bool CreatePlugin::genYml()
{
    QString path = QString("%1/../plugins/%2/%3.yml")
            .arg(QCoreApplication::applicationDirPath())
            .arg(ui->id_edt->text())
            .arg(ui->id_edt->text());
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;

    QString data;
    data += "# 插件名\n";
    data += QString("name: %1\n").arg(ui->name_edt->text());

    data += "# 插件ID\n";
    data += QString("id: %1\n").arg(ui->id_edt->text());

    data += "# 版本号\n";
    data += QString("version: %1\n").arg(ui->version_edt->text());

    data += "# 描述\n";
    data += QString("description: %1\n").arg(ui->description_edt->text());

    data += "# 类型[服务:0 窗体:1]\n";
    data += QString("type: %1\n").arg(ui->type_cbox->currentIndex());

    if (ui->type_cbox->currentIndex() == 1) {
        data += "# 菜单\n";
        data += "menu:\n";
        data += "    # 图标\n";
        data += QString("    icon: %1\n").arg(ui->icon_cbox->currentText());
        data += "    # 图标颜色\n";
        data += QString("    icon_color: \"%1\"\n").arg(ui->icon_color_edt->text());
        data += "    # 显示方式[内嵌:0 弹窗:1]\n";
        data += QString("    display_mode: %1\n").arg(ui->display_mode_cbox->currentIndex());
        data += "    # 菜单排序权重\n";
        data += QString("    sort_weight: %1\n").arg(ui->sort_weight_edt->text());
    }

    if (ui->dependent_list->selectedItems().size() > 0) {
        data += "# 依赖项\n";
        data += "dependents:\n";
        QString deps;
        for (auto item: ui->dependent_list->selectedItems()) {
            deps += QString("    - %1\n").arg(item->text());
        }
        data += deps;
    }

    file.write(data.toUtf8());
    file.close();
    return true;
}

bool CreatePlugin::genPro()
{
    QString path = QString("%1/../plugins/%2/%3.pro")
            .arg(QCoreApplication::applicationDirPath())
            .arg(ui->id_edt->text())
            .arg(ui->id_edt->text());
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return false;
    QString data;
    QFile t(":/template/template.pro");
    if (!t.open(QIODevice::ReadOnly)) {
        file.close();
        return false;
    }
    data = t.readAll();

    data.replace("{{id}}", ui->id_edt->text());

    if (ui->type_cbox->currentIndex() == 0) {
        data.replace("{{widget_cpps}}", "");
        data.replace("{{widget_hs}}", "");
        data.replace("{{widget_uis}}", "");
    }
    if (ui->type_cbox->currentIndex() == 1) {
        data.replace("{{widget_cpps}}", "widgets/mainwidget.cpp \\");
        data.replace("{{widget_hs}}", "widgets/mainwidget.h \\");
        data.replace("{{widget_uis}}", "widgets/mainwidget.ui \\");
    }

    file.write(data.toUtf8());
    file.close();
    t.close();
    return true;
}

bool CreatePlugin::copyFiles()
{
    QFile::copy(":/template/atomplugin_global.h", QString("%1/../plugins/%2/atomplugin_global.h")
                .arg(QCoreApplication::applicationDirPath())
                .arg(ui->id_edt->text()));
    QFile::copy(":/template/atomplugin.h", QString("%1/../plugins/%2/atomplugin.h")
                .arg(QCoreApplication::applicationDirPath())
                .arg(ui->id_edt->text()));
    if (ui->type_cbox->currentIndex() == 0) {
        QFile::copy(":/template/atomplugin_service.cpp", QString("%1/../plugins/%2/atomplugin.cpp")
                    .arg(QCoreApplication::applicationDirPath())
                    .arg(ui->id_edt->text()));
    }
    if (ui->type_cbox->currentIndex() == 1) {
        QString path = QString("%1/../plugins/%2/atomplugin.cpp")
                     .arg(QCoreApplication::applicationDirPath())
                     .arg(ui->id_edt->text());
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly))
            return false;
        QString data;
        QFile t(":/template/atomplugin_window.cpp");
        if (!t.open(QIODevice::ReadOnly)) {
            file.close();
            return false;
        }
        data = t.readAll();
        data.replace("{{id}}", ui->id_edt->text());
        file.write(data.toUtf8());
        file.close();
        t.close();

        QFile::copy(":/template/widgets/mainwidget.h", QString("%1/../plugins/%2/widgets/mainwidget.h")
                    .arg(QCoreApplication::applicationDirPath())
                    .arg(ui->id_edt->text()));
        QFile::copy(":/template/widgets/mainwidget.cpp", QString("%1/../plugins/%2/widgets/mainwidget.cpp")
                    .arg(QCoreApplication::applicationDirPath())
                    .arg(ui->id_edt->text()));
        QFile::copy(":/template/widgets/mainwidget.ui", QString("%1/../plugins/%2/widgets/mainwidget.ui")
                    .arg(QCoreApplication::applicationDirPath())
                    .arg(ui->id_edt->text()));
    }



    return true;
}

