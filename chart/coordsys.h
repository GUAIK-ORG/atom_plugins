#ifndef COORDSYS_H
#define COORDSYS_H

#include <QObject>
#include <QRect>

class CoordSys : public QObject
{
    Q_OBJECT
public:
    explicit CoordSys(QObject *parent = nullptr);

    // 更新物理窗口大小
    void updatePhysicsRect(const QRect& rect);
    // 更新频率范围
    void updateFreqRange(qreal minFreq, qreal maxFreq);
    // 更新能量范围
    void updatePowerRange(qreal minPower, qreal maxPower);
    // 设置开始频率
    void updateStartFreq(qreal freq);
    // 设置开始强度
    void updateStartPower(qreal power);
    // 获取开始频率和开始强度
    qreal getStartFreq() { return m_startFreq; }
    qreal getStartPower() { return m_startPower; }
    // 设置外边距
    void setTopMargin(int margin) { m_topMargin = margin; }
    void setRightMargin(int margin) { m_rightMargin = margin; }
    void setBottomMargin(int margin) { m_bottomMargin = margin; }
    void setLeftMargin(int margin) { m_leftMargin = margin; }

    // 判断全局坐标是否在有效区域内
    bool isEffective(const QPoint& point);
    // 获取有效区域(全局坐标系，左上角原点)
    QRect getEffectiveRect();
    // 获取有效区域（经过缩放X轴后的大小）
    QRect getZoomXEffectiveRect();
    // 获取一个像素点对应的频率值
    qreal pixel2Freq();
    // 获取一个像素点对应的强度值
    qreal pixel2Power();
    // 将有效区域坐标转换成全局坐标(左上角原点)
    bool getGPoint(const QPoint& ePoint, QPoint& gPoint);
    // 将全局坐标转换成有效区坐标（有效区左下角原点）
    bool getEPoint(const QPoint& gPoint, QPoint& ePoint);
    // 获取有效坐标对应的频率和强度
    void ePoint2Data(const QPoint& ePoint, qreal& freq, qreal& power);
    // 通过全局坐标获取有效区频率和强度
    void gPoint2Data(const QPoint& gPoint, qreal& freq, qreal& power);
    // 通过频率和强度获取有效坐标点
    QPoint data2EPoint(qreal freq, qreal power);

    // 放大
    void freqZoomIn();
    // 缩小
    void freqZoomOut();

private:
    QRect m_physicsRect;
    // 频率范围
    qreal m_minFreq;
    qreal m_maxFreq;
    // 开始频率
    qreal m_startFreq;

    // 能量范围
    qreal m_minPower;
    qreal m_maxPower;
    // 开始能量
    qreal m_startPower;

    // 边距
    int m_topMargin;
    int m_rightMargin;
    int m_bottomMargin;
    int m_leftMargin;

    // 频率缩放
    qreal m_freqScale;

signals:

};

#endif // COORDSYS_H
