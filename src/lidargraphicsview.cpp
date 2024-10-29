#include "lidargraphicsview.h"
#include "lidargraphicsscene.h"
#include <QScrollBar>

LidarGraphicsView::LidarGraphicsView(QWidget *parent) :
    GraphicsView(parent)
{
    _scene = new LidarGraphicsScene(this);
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    verticalScrollBar()->setSliderPosition(1);
    horizontalScrollBar()->setSliderPosition(1);
    setScene(_scene);
}

void LidarGraphicsView::processRangeMap(const RangeMap& rangeMap)
{
    _scene->processRangeMap(rangeMap);
}

void LidarGraphicsView::processScanAngle(double angle)
{
    _scene->processScanAngle_DEP(angle);
}

void LidarGraphicsView::setRadius(double meters)
{
    _scene->setRadius(meters);
}
