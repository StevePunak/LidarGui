#ifndef LIDARGRAPHICSSCENE_H
#define LIDARGRAPHICSSCENE_H

#include <Kanoop/gui/graphics/graphicsscene.h>

#include <QTimer>

#include <Kanoop/ratemonitor.h>

class ScanCircleGraphicsItem;
class SweepGraphicsItem;
class Point;
class ScannerGraphicsItem;
class RangeMap;
class LidarGraphicsScene : public GraphicsScene
{
    Q_OBJECT
public:
    explicit LidarGraphicsScene(QObject *parent = nullptr);

    void processRangeMap(const RangeMap& rangeMap);
    void processScanAngle_DEP(double angle);

    void setRadius(double meters);

    Point sweepCenterPoint() const;
    double pixelsPerMeter() const;
    double radiusMeters() const;

private:
    ScannerGraphicsItem* _scannerItem;
    SweepGraphicsItem* _sweepItem;
    ScanCircleGraphicsItem* _circleItem;

    RateMonitor _sweepRateMonitor;

    QDateTime _startTime;
    QTimer _sweepTimer;

    double _sweepAngle = 0;
    double _sweepStep = 0;

signals:

private slots:
    void onTimerExpired();

};

#endif // LIDARGRAPHICSSCENE_H
