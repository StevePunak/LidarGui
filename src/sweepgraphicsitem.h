#ifndef SWEEPGRAPHICSITEM_H
#define SWEEPGRAPHICSITEM_H
#include <Kanoop/gui/graphics/linegraphicsitem.h>

class LidarGraphicsScene;
class SweepGraphicsItem : public LineGraphicsItem
{
public:
    SweepGraphicsItem(LidarGraphicsScene* scene, QGraphicsItem* parent = nullptr);

public:
    void setAngle(double angle);

private:
    LidarGraphicsScene* _scene = nullptr;

    static const QColor LineColor;
};

#endif // SWEEPGRAPHICSITEM_H
