#include "lidardisplaywidget.h"

#include <QPainter>
#include <QPainterPath>
#include <QResizeEvent>

#include <Kanoop/geometry/rectangle.h>
#include <Kanoop/log.h>
#include <rplidarqt/rangemap.h>

namespace Colors = QColorConstants::Svg;

const double LidarDisplayWidget::SweepAngle = 5.0;       // how much to clear on the sweep
const QColor LidarDisplayWidget::BackgroundColor = Colors::black;
const QColor LidarDisplayWidget::PointColor = Colors::aquamarine;

LidarDisplayWidget::LidarDisplayWidget(QWidget *parent) :
    QFrame(parent)
{
}

void LidarDisplayWidget::processSample(double bearing, double range, const QDateTime& timestamp)
{
    Q_UNUSED(timestamp)

    Rectangle rect = _pixmap.rect();

    double smallest = qMin(rect.width(), rect.height());
    double pixelsPerMeter = (smallest / 2) / _radius;

    Point centerPoint = rect.centerPoint();

    QPainter painter(&_pixmap);

    // clear ahead for sweep
    Line l1(centerPoint, bearing, _radius * pixelsPerMeter);
    Line l2(centerPoint, bearing + SweepAngle, _radius * pixelsPerMeter);
    QList<QPointF> sweepPoints = {
        centerPoint, l1.p2(), l2.p2(), centerPoint,
    };
    QPolygonF polygon(sweepPoints);

    QPainterPath path;
    path.addPolygon(polygon);

    painter.fillPath(path, QBrush(Colors::white));

    Point point = FlatGeo::getPoint(centerPoint, bearing, range * pixelsPerMeter);

    painter.setPen(Colors::blue);
    painter.drawPoint(point);

    update();
}

void LidarDisplayWidget::processRangeMap(const RangeMap& rangeMap)
{
    _pixmap.fill(BackgroundColor);

    Rectangle rect = _pixmap.rect();

    double smallest = qMin(rect.width(), rect.height());
    double pixelsPerMeter = (smallest / 2) / _radius;

    Point centerPoint = rect.centerPoint();
    QPainter painter(&_pixmap);

    QList<double> vectors = rangeMap.vectors();
    double bearing = 0;
    for(int i = 0;i < vectors.count();i++, bearing += rangeMap.vectorAngle()) {
        Point point = FlatGeo::getPoint(centerPoint, bearing, vectors.at(i) * pixelsPerMeter);
        painter.setPen(PointColor);
        painter.drawPoint(point);
    }

    update();
}

void LidarDisplayWidget::resizeEvent(QResizeEvent* event)
{
    QFrame::resizeEvent(event);

    _pixmap = QPixmap(event->size());
    _pixmap.fill(BackgroundColor);
}

void LidarDisplayWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.drawPixmap(rect(), _pixmap);
}
