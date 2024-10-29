#include "lidargraphicsscene.h"

#include "scancirclegraphicsitem.h"
#include "scannergraphicsitem.h"
#include "sweepgraphicsitem.h"

#include <Kanoop/geometry/rectangle.h>
#include <Kanoop/geometry/size.h>

#include <QPainter>

#include <rplidarqt/rangemap.h>

#include <Kanoop/timespan.h>

LidarGraphicsScene::LidarGraphicsScene(QObject* parent) :
    GraphicsScene(parent),
    _startTime(QDateTime::currentDateTimeUtc())
{
    Rectangle rect(0, 0, 2000, 1000);
    setSceneRect(rect);

    _scannerItem = new ScannerGraphicsItem(this);
    addItem(_scannerItem);

    _sweepItem = new SweepGraphicsItem(this, _scannerItem);
    _sweepItem->setVisible(true);

    _circleItem = new ScanCircleGraphicsItem(this, _scannerItem);
    _circleItem->setVisible(true);

    connect(_scannerItem, &ScannerGraphicsItem::pixelsPerMeterChanged, _circleItem, &ScanCircleGraphicsItem::setPixelsPerMeter);

    // connect(&_sweepTimer, &QTimer::timeout, this, &LidarGraphicsScene::onTimerExpired);
    // _sweepStep = 5;
    // _sweepTimer.start(5);
}

void LidarGraphicsScene::processRangeMap(const RangeMap& rangeMap)
{
    static TimeSpan SweepTimerInterval = TimeSpan::fromMilliseconds(10);

    _scannerItem->processRangeMap(rangeMap);

    _sweepItem->setAngle(0);
    _sweepItem->setVisible(!_sweepItem->isVisible());
return;
    _sweepRateMonitor.addEvent();
    if(QDateTime::currentDateTimeUtc() > _startTime.addSecs(1)) {
        double sweepsPerSecond = _sweepRateMonitor.eventsPerSecond();

        double sweepStep = std::round((360.0 * sweepsPerSecond) * SweepTimerInterval.totalSeconds());
        if(sweepStep != _sweepStep) {
            _sweepStep = sweepStep;
            logText(LVL_DEBUG, QString("%1 sweeps p/s rate: %2").arg(_sweepRateMonitor.eventsPerSecond()).arg(_sweepStep));
            _sweepTimer.start(SweepTimerInterval.totalMilliseconds());
            _sweepAngle = 0;
        }
    }
}

void LidarGraphicsScene::processScanAngle_DEP(double angle)
{
    return;
    static double lastAngle = 0;
    if(std::abs(angle - lastAngle) > 20) {
        _sweepItem->setAngle((int)angle);
        lastAngle = angle;
    }
}

void LidarGraphicsScene::setRadius(double meters)
{
    _scannerItem->setRadius(meters);
    _circleItem->setPixelsPerMeter(meters);
}

Point LidarGraphicsScene::sweepCenterPoint() const
{
    return _scannerItem->sweepCenterPoint();
}

double LidarGraphicsScene::pixelsPerMeter() const
{
    return _scannerItem->pixelsPerMeter();
}

double LidarGraphicsScene::radiusMeters() const
{
    return _scannerItem->radiusMeters();
}

void LidarGraphicsScene::onTimerExpired()
{
    _sweepAngle += _sweepStep;
    if(_sweepAngle >= 360) {
        _sweepAngle = 0;
    }
    _sweepItem->setAngle(_sweepAngle);
}

