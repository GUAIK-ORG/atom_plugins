#ifndef CHARTBASE_H
#define CHARTBASE_H

#include <QWidget>
#include <QBitmap>

class ChartBase : public QWidget
{
    Q_OBJECT
public:
    explicit ChartBase(QWidget *parent = nullptr);

public:
    virtual void updateData() = 0;

signals:

};

#endif // CHARTBASE_H
