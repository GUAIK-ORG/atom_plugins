#ifndef SPECTRUM_H
#define SPECTRUM_H

#include "chartbase.h"
#include "coordsys.h"

#include <QMouseEvent>
#include <QResizeEvent>

class Spectrum : public ChartBase
{
    Q_OBJECT
public:
    explicit Spectrum(CoordSys* coordSys, QWidget *parent = nullptr);


protected:
    void paintEvent(QPaintEvent* e) override;
    void mouseMoveEvent(QMouseEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;
    void wheelEvent(QWheelEvent *event) override;

    void updateData() override;

private:
    QBitmap* m_bmp;
    CoordSys* m_coordSys;

    int m_freqDivCount;
    int m_powerDivCount;

    int m_freqMargin;
    int m_powerMargin;

    QPoint m_curGPos;
    QPoint m_curEPos;

    qreal m_curFreq;
    qreal m_curPower;

    bool m_mouseLeftBtnPressed;
    QPoint m_mouseLeftBtnPressedPos;

    bool m_mouseRightBtnPressed;
    QPoint m_mouseRightBtnPressedPos;

signals:

};

#endif // SPECTRUM_H
