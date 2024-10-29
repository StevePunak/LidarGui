#ifndef LIDARGUITYPES_H
#define LIDARGUITYPES_H
#include <QGraphicsItem>

namespace Lidar
{
enum GraphicItemTypes {
    ScannerBackground = QGraphicsItem::UserType + 1,
    Sweep,
    CircleAround,
};

} // namespace

#endif // LIDARGUITYPES_H
