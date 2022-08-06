#include "mainwidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>
#include <QThread>
#include <QDateTime>
#include <QToolButton>
#include <QApplication>
#include <iwindow.h>

MainWidget::MainWidget(IContext* ctx, QWidget *parent)
    : QWidget(parent)
    , m_ctx(ctx)
{
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("background-color:rgb(0,204,106);color:#ffffff");
    this->setFixedHeight(30);
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);

    QLabel* title = new QLabel();
    title->setText("Atom");
    title->setStyleSheet("color:#ffffff;font-family: \"Microsoft YaHei\";font-weight:bold;font-size:20px;");

    QToolButton* fullScreenBtn = new QToolButton();
    fullScreenBtn->setFixedSize(25, 25);
    fullScreenBtn->setText("F");
    connect(fullScreenBtn, &QPushButton::clicked, this, [=](){
        IWindowManager* win;
        if (0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER, (void**)&win)) {
            if (!win->isFullScreen()) {
                win->showFullScreen();
            } else {
                win->showNormal();
            }
        }
    });

    QToolButton* minBtn = new QToolButton();
    minBtn->setFixedSize(25, 25);
    minBtn->setText("-");
    connect(minBtn, &QPushButton::clicked, this, [=](){
        IWindowManager* win;
        if (0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER, (void**)&win)) {
            win->showMinimize();
        }
    });

    QToolButton* maxBtn = new QToolButton();
    maxBtn->setFixedSize(25, 25);
    maxBtn->setText("□");
    connect(maxBtn, &QPushButton::clicked, this, [=](){
        IWindowManager* win;
        if (0 == m_ctx->query(QUERY_TYPE::WINDOW_MANAGER, (void**)&win)) {
            if (!win->isMaximize()) {
                win->showMaximize();
            } else {
                win->showNormal();
            }
        }
    });

    QToolButton* closeBtn = new QToolButton();
    closeBtn->setFixedSize(25, 25);
    closeBtn->setText("×");
    connect(closeBtn, &QToolButton::clicked, this, [=](){
        QMessageBox::StandardButton result = QMessageBox::information(NULL, "提示", "你确定你要退出么？", QMessageBox::Yes|QMessageBox::No);
        if (result == QMessageBox::Yes) {
            qApp->exit(0);
        }
    });

    mainLayout->addSpacing(20);
    mainLayout->addWidget(title);
    mainLayout->addStretch();
    mainLayout->addWidget(fullScreenBtn);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(minBtn);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(maxBtn);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(closeBtn);
    mainLayout->addSpacing(10);

    this->setLayout(mainLayout);
}

void MainWidget::onMessage(QString id, void *pArg)
{

}

