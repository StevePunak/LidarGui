#include "scancirclegraphicsitem.h"
#include "lidarguitypes.h"
#include "lidargraphicsscene.h"

#include <Kanoop/geometry/rectangle.h>

namespace Colors = QColorConstants::Svg;

const QColor ScanCircleGraphicsItem::LineColor = Colors::lightgreen;

ScanCircleGraphicsItem::ScanCircleGraphicsItem(LidarGraphicsScene* scene, QGraphicsItem* parent) :
    EllipseGraphicsItem(Lidar::CircleAround, parent),
    _scene(scene)
{
    setWidth(2);
    setColor(LineColor);
    setZValue(1);
    Rectangle rect = Rectangle::fromCenterPoint(_scene->sweepCenterPoint(), _scene->pixelsPerMeter() * _scene->radiusMeters());
    setRect(rect);
}

void ScanCircleGraphicsItem::setPixelsPerMeter(double value)
{
    Rectangle rect = Rectangle::fromCenterPoint(_scene->sweepCenterPoint(), value * _scene->radiusMeters() / 2);
    setRect(rect);
}
