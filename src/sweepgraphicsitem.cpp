#include "sweepgraphicsitem.h"
#include "lidarguitypes.h"
#include "lidargraphicsscene.h"

#include <Kanoop/geometry/line.h>
#include <Kanoop/geometry/rectangle.h>

namespace Colors = QColorConstants::Svg;

const QColor SweepGraphicsItem::LineColor = Colors::red;

SweepGraphicsItem::SweepGraphicsItem(LidarGraphicsScene* scene, QGraphicsItem* parent) :
    LineGraphicsItem(Lidar::Sweep, parent),
    _scene(scene)
{
    setWidth(2);
    setColor(LineColor);
    setZValue(1);
}

void SweepGraphicsItem::setAngle(double angle)
{
    // logText(LVL_DEBUG, QString("Angle: %1").arg(angle));
    double length = 250;    // _scene->pixelsPerMeter() * _scene->radiusMeters();
    Line line(_scene->sweepCenterPoint(), angle, length);
    setLine(line.toQLineF());
    update(_scene->sceneRect());
}
