#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QThread>
#include <QFile>

MainWidget::MainWidget(IContext* ctx, QWidget *parent)
    : QWidget(parent)
    , m_ctx(ctx)
{
    QPalette pal(this->palette());
    pal.setColor(QPalette::Background, QColor("#132031"));
    this->setAutoFillBackground(true);
    this->setPalette(pal);

    QFile qss(":/style.qss");
    if( qss.open(QFile::ReadOnly)) {
    QString style = QLatin1String(qss.readAll());
        this->setStyleSheet(style);
        qss.close();
    }

    m_createPlugin = new CreatePlugin(m_ctx, this);

    QHBoxLayout *hLay = new QHBoxLayout();
    hLay->addStretch();
    hLay->addWidget(m_createPlugin);
    hLay->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addStretch();
    mainLayout->addLayout(hLay);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

MainWidget::~MainWidget()
{
}

