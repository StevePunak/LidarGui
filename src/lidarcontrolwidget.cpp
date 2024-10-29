#include "lidarcontrolwidget.h"
#include "ui_lidarcontrolwidget.h"

LidarControlWidget::LidarControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LidarControlWidget)
{
    ui->setupUi(this);
}

LidarControlWidget::~LidarControlWidget()
{
    delete ui;
}
