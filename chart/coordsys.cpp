#include "coordsys.h"
#include <QDebug>

CoordSys::CoordSys(QObject *parent)
    : QObject(parent)
    , m_topMargin(0)
    , m_rightMargin(0)
    , m_bottomMargin(0)
    , m_leftMargin(0)
    , m_freqScale(1.0)
{

}

void CoordSys::updatePhysicsRect(const QRect &rect)
{
    m_physicsRect = rect;
}

void CoordSys::updateFreqRange(qreal minFreq, qreal maxFreq)
{
    m_minFreq = minFreq;
    m_maxFreq = maxFreq;
}

void CoordSys::updatePowerRange(qreal minPower, qreal maxPower)
{
    m_minPower = minPower;
    m_maxPower = maxPower;
}

void CoordSys::updateStartFreq(qreal freq)
{
    QRect r1 = getZoomXEffectiveRect();
    QRect r2 = getEffectiveRect();
    qreal limit = m_minFreq + (r1.width() - r2.width()) * pixel2Freq();

    if (freq < m_minFreq) m_startFreq = m_minFreq;
    else if (freq > limit) m_startFreq = limit;
    else m_startFreq = freq;
}

void CoordSys::updateStartPower(qreal power)
{
    m_startPower = power;
}


void CoordSys::ePoint2Data(const QPoint& ePoint, qreal &freq, qreal &power)
{
//    QRect effRect = getEffectiveRect();
//    QRect effRect = getZoomXEffectiveRect();
//    freq = (m_maxFreq - m_minFreq) / effRect.width() * ePoint.x() + m_minFreq;
//    power = (m_maxPower - m_minPower) / effRect.height() * ePoint.y() + m_minPower;
    freq = pixel2Freq() * ePoint.x() + m_startFreq;
    power = pixel2Power() * ePoint.y() + m_startPower;
}

void CoordSys::gPoint2Data(const QPoint &gPoint, qreal &freq, qreal &power)
{
    QPoint ePoint;
    if(getEPoint(gPoint, ePoint)) {
        ePoint2Data(ePoint, freq, power);
    }
}

QPoint CoordSys::data2EPoint(qreal freq, qreal power)
{
//    QRect effRect = getEffectiveRect();
    QRect effRect = getZoomXEffectiveRect();
    int realX = effRect.width() / (m_maxFreq - m_minFreq) * (freq - m_startFreq);
    int realY = effRect.height() / (m_maxPower - m_minPower) * (power - m_startPower);

    return QPoint(realX, realY);
}

void CoordSys::freqZoomIn()
{
    m_freqScale += 0.05;
    m_freqScale = m_freqScale > 2.0 ? 2.0 : m_freqScale;
    qDebug() << m_freqScale;
}

void CoordSys::freqZoomOut()
{
    m_freqScale -= 0.05;
    m_freqScale = m_freqScale < 1.0 ? 1.0 : m_freqScale;
    qDebug() << m_freqScale;
}

bool CoordSys::isEffective(const QPoint& point)
{
    return (m_leftMargin <= point.x() && point.x() <= m_physicsRect.width() - m_rightMargin) &&
            (m_topMargin <= point.y() && point.y() <= m_physicsRect.height() - m_bottomMargin);
}

QRect CoordSys::getEffectiveRect()
{
    int realWidth = m_physicsRect.width() - (m_leftMargin + m_rightMargin);
    int realHeight = m_physicsRect.height() - (m_topMargin + m_bottomMargin);
    return QRect(m_leftMargin, m_physicsRect.height() - m_bottomMargin, realWidth, realHeight);
}

QRect CoordSys::getZoomXEffectiveRect()
{
    QRect rect = getEffectiveRect();
    rect.setWidth(rect.width() * m_freqScale);
    return rect;
}

qreal CoordSys::pixel2Freq()
{
    QRect rect = getZoomXEffectiveRect();
    return (m_maxFreq - m_minFreq) / rect.width();
}

qreal CoordSys::pixel2Power()
{
    QRect rect = getZoomXEffectiveRect();
    return (m_maxPower - m_minPower) / rect.height();
}

bool CoordSys::getGPoint(const QPoint &ePoint, QPoint& gPoint)
{
    QRect effRect = getEffectiveRect();
    if (ePoint.x() < 0 || ePoint.x() > effRect.width() || ePoint.y() < 0 || ePoint.y() > effRect.height()) return false;
    gPoint.setX(ePoint.x() + m_leftMargin);
    gPoint.setY(m_physicsRect.height() - (ePoint.y() + m_bottomMargin));
    return true;
}

bool CoordSys::getEPoint(const QPoint &gPoint, QPoint &ePoint)
{
    if(!isEffective(gPoint)) return false;
    ePoint.setX(gPoint.x() - m_leftMargin);
    ePoint.setY(m_physicsRect.height() - (gPoint.y() + m_bottomMargin));
    return true;
}
