#ifndef LIDARDISPLAYWIDGET_H
#define LIDARDISPLAYWIDGET_H

#include <QFrame>

class RangeMap;
class LidarDisplayWidget : public QFrame
{
    Q_OBJECT
public:
    explicit LidarDisplayWidget(QWidget *parent = nullptr);

public slots:
    void processSample(double bearing, double range, const QDateTime& timestamp);
    void processRangeMap(const RangeMap& rangeMap);
    void setRadius(double meters) { _radius = meters; update(); }

private:
    virtual void resizeEvent(QResizeEvent* event) override;
    virtual void paintEvent(QPaintEvent* event) override;

    QPixmap _pixmap;
    double _radius = 10;

    static const double SweepAngle;
    static const QColor BackgroundColor;
    static const QColor PointColor;

signals:
};

#endif // LIDARDISPLAYWIDGET_H
