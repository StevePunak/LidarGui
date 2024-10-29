#ifndef SCANCIRCLEGRAPHICSITEM_H
#define SCANCIRCLEGRAPHICSITEM_H
#include <Kanoop/gui/graphics/ellipsegraphicsitem.h>
#include <Kanoop/gui/graphics/qobjectgraphicsitem.h>

class LidarGraphicsScene;
class ScanCircleGraphicsItem : public QObjectGraphicsItem,
                               public EllipseGraphicsItem
{
    Q_OBJECT
public:
    ScanCircleGraphicsItem(LidarGraphicsScene* scene, QGraphicsItem* parent = nullptr);

public slots:
    void setPixelsPerMeter(double value);

private:
    LidarGraphicsScene* _scene = nullptr;

    static const QColor LineColor;
};

#endif // SCANCIRCLEGRAPHICSITEM_H
