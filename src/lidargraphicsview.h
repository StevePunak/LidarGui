#ifndef LIDARGRAPHICSVIEW_H
#define LIDARGRAPHICSVIEW_H

#include <Kanoop/gui/graphics/graphicsview.h>

class LidarGraphicsScene;
class RangeMap;
class LidarGraphicsView : public GraphicsView
{
    Q_OBJECT
public:
    explicit LidarGraphicsView(QWidget *parent = nullptr);

public slots:
    void processRangeMap(const RangeMap& rangeMap);
    void processScanAngle(double angle);
    void setRadius(double meters);

private:
    LidarGraphicsScene* _scene = nullptr;

signals:

};

#endif // LIDARGRAPHICSVIEW_H
