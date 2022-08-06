#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "icontext.h"
#include "imessage.h"
#include "imq.h"

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget, public IMessageHandler, public IMQMessageHandler
{
    Q_OBJECT
public:
    explicit MainWidget(IContext* ctx, QWidget *parent = nullptr);
    ~MainWidget();

private:
    Ui::MainWidget *ui;
    IContext* m_ctx;

protected:
    /**
     * @brief 消息回调函数（当前进程通讯）
     * @param id 事件id
     * @param pArg 参数指针
     */
    void onMessage(QString id, void *pArg) override;

    /**
     * @brief 消息队列回调函数（多进程通讯）
     * @param topic 主题
     * @param data 数据
     */
    void onMessage(QString topic, const QByteArray &data) override;


signals:

public slots:
};

#endif // MAINWIDGET_H
