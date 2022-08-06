#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "iwindow.h"
#include "ilog.h"

MainWidget::MainWidget(IContext* ctx, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
    , m_ctx(ctx)
{
    ui->setupUi(this);
}

MainWidget::~MainWidget()
{
    delete ui;
}


void MainWidget::onMessage(QString id, void *pArg)
{

}

void MainWidget::onMessage(QString topic, const QByteArray &data)
{

}

