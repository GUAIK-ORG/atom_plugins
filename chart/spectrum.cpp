#include "spectrum.h"
#include <QPainter>
#include <QDebug>

Spectrum::Spectrum(CoordSys* coordSys, QWidget *parent)
    : ChartBase(parent)
    , m_coordSys(coordSys)
    , m_mouseLeftBtnPressed(false)
    , m_mouseRightBtnPressed(false)
{

    setMouseTracking(true);

    m_freqMargin = 50;
    m_powerMargin = 80;

    m_freqDivCount = 10;
    m_powerDivCount = 10;

    m_coordSys->updatePhysicsRect(this->rect());
    m_coordSys->updateFreqRange(10000.0, 14000.0);
    m_coordSys->updateStartFreq(10000.0);
    m_coordSys->updatePowerRange(-60, 60);
    m_coordSys->updateStartPower(-60);
    m_coordSys->setLeftMargin(m_powerMargin);
    m_coordSys->setBottomMargin(m_freqMargin);

    QRect effectiveRect = m_coordSys->getEffectiveRect();
    m_curGPos = QPoint(effectiveRect.x(), effectiveRect.y());

//    setFixedHeight(200);
}

void Spectrum::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());

    QRect effectiveRect = m_coordSys->getEffectiveRect();

    // 绘制表格
    int colWidth = effectiveRect.width() / m_freqDivCount;
    int colHeight = effectiveRect.height() / m_powerDivCount;

    painter.setPen(QPen(QBrush(QColor(0x50, 0x50, 0x50)), 0.8, Qt::DotLine));
    int delta = 20;
    for(int i=0; i< m_freqDivCount; i++) {
        QPoint gPointA;
        QPoint gPointB;
        m_coordSys->getGPoint(QPoint(i * colWidth, effectiveRect.height()), gPointA);
        m_coordSys->getGPoint(QPoint(i * colWidth, 0), gPointB);
        painter.drawLine(gPointA, gPointB);

        QFont font;
        font.setPointSize(10);
        font.setFamily("Microsoft YaHei");
        font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
        painter.setFont(font);
        qreal freq;
        qreal power;
        m_coordSys->ePoint2Data(QPoint(i * colWidth, 0), freq, power);
        QFontMetricsF fontMetrics(font);
        QString data = QString::asprintf("%.2f",freq);
        int w = fontMetrics.width(data);
        int h = fontMetrics.height();
        painter.drawText(gPointB.x() - w / 2, effectiveRect.y() + delta, w, h, Qt::AlignCenter, data);
    }

    for(int i=0; i< m_powerDivCount; i++) {
        QPoint gPointA;
        QPoint gPointB;
        m_coordSys->getGPoint(QPoint(0, i * colHeight), gPointA);
        m_coordSys->getGPoint(QPoint(effectiveRect.width(), i * colHeight), gPointB);
        painter.drawLine(gPointA, gPointB);

        QFont font;
        font.setPointSize(10);
        font.setFamily("Microsoft YaHei");
        font.setLetterSpacing(QFont::AbsoluteSpacing, 0);
        painter.setFont(font);
        qreal freq;
        qreal power;
        m_coordSys->ePoint2Data(QPoint(0, i * colHeight), freq, power);
        QFontMetricsF fontMetrics(font);
        QString data = QString::asprintf("%.2f",power);
        int w = fontMetrics.width(data);
        int h = fontMetrics.height();
        painter.drawText(effectiveRect.x() - w - delta, gPointB.y() - h / 2, w, h, Qt::AlignCenter, data);
    }

    // 绘制辅助线
    {
        painter.setPen(QPen(QBrush(Qt::green), 0.8, Qt::DashDotLine));
        painter.drawLine(effectiveRect.x(), m_curGPos.y(), effectiveRect.x()+effectiveRect.width(), m_curGPos.y());
        painter.drawLine(m_curGPos.x(), effectiveRect.y() - effectiveRect.height(), m_curGPos.x(), effectiveRect.y());
    }

    // 绘制频率和强度文字标签
    qreal freq;
    qreal power;
    m_coordSys->gPoint2Data(m_curGPos, freq, power);
    painter.setBrush(Qt::green);

    QFont font;
    font.setPointSize(13);
    font.setFamily("Microsoft YaHei");
    font.setLetterSpacing(QFont::AbsoluteSpacing, 1);
    painter.setFont(font);

    QFontMetricsF fontMetrics(font);
    QString data = QString::asprintf("F:%.2f P:%.2f", freq, power);
    int labWidth = fontMetrics.width(data);
    int labHeight = fontMetrics.height();

    int labDeltaX = 0;
    int labDeltaY = 0;

    QPoint ePoint;
    if (m_coordSys->getEPoint(m_curGPos, ePoint)) {
        bool x = ePoint.x() + labWidth > effectiveRect.width();
        bool y = ePoint.y() + labHeight > effectiveRect.height();
        if (x) {
            labDeltaX = -labWidth;
        }
        if (y) {
            labDeltaY = labHeight;
            if (!x) labDeltaX = 15;    // 防止鼠标遮挡文字
        }
        if (ePoint.x() + labWidth + labDeltaX > effectiveRect.width()) {
            labDeltaX = -labWidth;
        }
    }
    painter.drawRect(m_curGPos.x() + labDeltaX, m_curGPos.y() - labHeight + labDeltaY, labWidth, labHeight);
    painter.setPen(QColor(0x40, 0x50, 0x60));
    painter.drawText(m_curGPos.x() + labDeltaX, m_curGPos.y() - labHeight + labDeltaY, labWidth, labHeight, Qt::AlignCenter, data);
}

void Spectrum::mouseMoveEvent(QMouseEvent *e)
{
    if(m_coordSys->isEffective(e->pos())) {
        m_curGPos = e->pos();
        m_coordSys->getEPoint(m_curGPos, m_curEPos);
        m_coordSys->ePoint2Data(m_curEPos, m_curFreq, m_curPower);
        update();
    }
    if (m_mouseLeftBtnPressed) {
        QPoint deltaPos = e->pos() - m_mouseLeftBtnPressedPos;
        m_mouseLeftBtnPressedPos = e->pos();
        if (deltaPos.x() > 0) {
            m_coordSys->updateStartFreq(m_coordSys->getStartFreq() - m_coordSys->pixel2Freq());
        } else if (deltaPos.x() < 0) {
            m_coordSys->updateStartFreq(m_coordSys->getStartFreq() + m_coordSys->pixel2Freq());
        }
    }
    if (m_mouseRightBtnPressed) {
        QPoint deltaPos = e->pos() - m_mouseRightBtnPressedPos;
        m_mouseRightBtnPressedPos = e->pos();
        if (deltaPos.y() > 0) {
            m_coordSys->updateStartPower(m_coordSys->getStartPower() + m_coordSys->pixel2Power());
        } else if (deltaPos.y() < 0) {
            m_coordSys->updateStartPower(m_coordSys->getStartPower() - m_coordSys->pixel2Power());
        }
    }
}

void Spectrum::mousePressEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton && m_coordSys->isEffective(e->pos())) {
        setCursor(Qt::ClosedHandCursor);
        m_mouseLeftBtnPressed = true;
        m_mouseLeftBtnPressedPos = e->pos();
    }

    if (e->button() & Qt::RightButton && m_coordSys->isEffective(e->pos())) {
        setCursor(Qt::ClosedHandCursor);
        m_mouseRightBtnPressed = true;
        m_mouseRightBtnPressedPos = e->pos();
    }
}

void Spectrum::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() & Qt::LeftButton && m_coordSys->isEffective(e->pos())) {
        setCursor(Qt::ArrowCursor);
        m_mouseLeftBtnPressed = false;
        m_mouseLeftBtnPressedPos = QPoint(0, 0);
    }

    if (e->button() & Qt::RightButton && m_coordSys->isEffective(e->pos())) {
        setCursor(Qt::ArrowCursor);
        m_mouseRightBtnPressed = false;
        m_mouseRightBtnPressedPos = QPoint(0, 0);
    }
}

void Spectrum::resizeEvent(QResizeEvent *e)
{
    Q_UNUSED(e);
    m_coordSys->updatePhysicsRect(this->rect());
}

void Spectrum::wheelEvent(QWheelEvent *event)
{
    if (m_coordSys->isEffective(event->pos())) {
        if(event->delta() > 0) {
            m_coordSys->freqZoomOut();
        } else if (event->delta() < 0) {
            m_coordSys->freqZoomIn();
        }
        m_coordSys->updateStartFreq(m_curFreq - m_curEPos.x() * m_coordSys->pixel2Freq());
        update();
    }

}

void Spectrum::updateData()
{

}
