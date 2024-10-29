#include "scannergraphicsitem.h"
#include "lidarguitypes.h"
#include "lidargraphicsscene.h"

#include <Kanoop/geometry/rectangle.h>

#include <QPainter>

namespace Colors = QColorConstants::Svg;

const double ScannerGraphicsItem::SweepAngle = 5.0;       // how much to clear on the sweep
const QColor ScannerGraphicsItem::BackgroundColor = Colors::black;
const QColor ScannerGraphicsItem::PointColor = Colors::aquamarine;


ScannerGraphicsItem::ScannerGraphicsItem(LidarGraphicsScene* scene, QGraphicsItem* parent) :
    PixmapGraphicsItem(Lidar::ScannerBackground, parent),
    _scene(scene)
{
    _pixmap = QPixmap(_scene->sceneRect().size().toSize());
    _pixmap.fill(BackgroundColor);
}

void ScannerGraphicsItem::processRangeMap(const RangeMap& rangeMap)
{
    _pixmap.fill(BackgroundColor);

    Rectangle rect = _pixmap.rect();

    double smallest = qMin(rect.width(), rect.height());
    double pixelsPerMeter = (smallest / 2) / _radius;
    if(pixelsPerMeter != _pixelsPerMeter) {
        _pixelsPerMeter = pixelsPerMeter;
        emit pixelsPerMeterChanged(_pixelsPerMeter);
    }

    Point centerPoint = rect.centerPoint();
    QPainter painter(&_pixmap);

    QList<double> vectors = rangeMap.vectors();
    double bearing = 0;
    for(int i = 0;i < vectors.count();i++, bearing += rangeMap.vectorAngle()) {
        Point point = FlatGeo::getPoint(centerPoint, bearing, vectors.at(i) * _pixelsPerMeter);
        painter.setPen(PointColor);
        painter.drawPoint(point);
    }

    setPixmap(_pixmap);
}

Point ScannerGraphicsItem::sweepCenterPoint() const
{
    return mapToScene(_pixmap.rect().center());
}
