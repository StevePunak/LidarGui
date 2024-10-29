#ifndef LIDARCONTROLWIDGET_H
#define LIDARCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class LidarControlWidget;
}

class LidarControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LidarControlWidget(QWidget *parent = nullptr);
    ~LidarControlWidget();

private:
    Ui::LidarControlWidget *ui;
};

#endif // LIDARCONTROLWIDGET_H
