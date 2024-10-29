#ifndef SCANNERGRAPHICSITEM_H
#define SCANNERGRAPHICSITEM_H
#include <Kanoop/gui/graphics/pixmapgraphicsitem.h>
#include <Kanoop/gui/graphics/qobjectgraphicsitem.h>

#include <rplidarqt/rangemap.h>

class Point;
class LidarGraphicsScene;
class ScannerGraphicsItem : public QObjectGraphicsItem,
                            public PixmapGraphicsItem

{
    Q_OBJECT
public:
    ScannerGraphicsItem(LidarGraphicsScene* scene, QGraphicsItem* parent = nullptr);

public:
    void processRangeMap(const RangeMap& rangeMap);
    void setRadius(double meters) { _radius = meters; update(); }

    Point sweepCenterPoint() const;
    double radiusMeters() const { return _radius; }
    double pixelsPerMeter() const { return _pixelsPerMeter; }

private:
    LidarGraphicsScene* _scene = nullptr;

    QPixmap _pixmap;
    double _radius = 10;
    double _pixelsPerMeter = 1;

    static const double SweepAngle;
    static const QColor BackgroundColor;
    static const QColor PointColor;

signals:
    void pixelsPerMeterChanged(double value);
};

#endif // SCANNERGRAPHICSITEM_H
