#include "lidarguimainwindow.h"
#include "settings.h"
#include "ui_lidarguimainwindow.h"

#include <rplidarqt.h>

#include <Kanoop/datetimeutil.h>

#include <Kanoop/gui/utility/unicode.h>

const double LidarGuiMainWindow::RadiusDivisor = .25;

LidarGuiMainWindow::LidarGuiMainWindow(QWidget *parent) :
    MainWindowBase("lidargui", parent),
    ui(new Ui::LidarGuiMainWindow)
{
    ui->setupUi(this);

    initializeBase();

    _lidar = new RPLidar("/dev/ttyUSB3");
    _lidar->setAngleOffset(Settings::instance()->rotation());

    connect(ui->pushStartMotor, &QPushButton::clicked, this, &LidarGuiMainWindow::onStartMotorClicked);
    connect(ui->pushStopMotor, &QPushButton::clicked, this, &LidarGuiMainWindow::onStopMotorClicked);
    connect(ui->pushStartScan, &QPushButton::clicked, this, &LidarGuiMainWindow::onStartScanClicked);
    connect(ui->pushStopScan, &QPushButton::clicked, this, &LidarGuiMainWindow::onStopScanClicked);
    connect(ui->pushGetSampleRate, &QPushButton::clicked, this, &LidarGuiMainWindow::onGetSampleRateClicked);
    connect(ui->pushGetAccBoard, &QPushButton::clicked, this, &LidarGuiMainWindow::onGetAccBoardClicked);
    connect(ui->pushGetDeviceInfo, &QPushButton::clicked, this, &LidarGuiMainWindow::onGetDeviceInfoClicked);

    connect(ui->radiusSlider, &QSlider::valueChanged, this, &LidarGuiMainWindow::onRadiusSliderChanged);
    connect(ui->rotationSlider, &QSlider::valueChanged, this, &LidarGuiMainWindow::onRotationSliderChanged);

    connect(ui->checkHexLog, &QCheckBox::toggled, _lidar, &RPLidar::setHexLogEnabled);

    ui->radiusSlider->setValue(Settings::instance()->radius() / RadiusDivisor);
    ui->rotationSlider->setValue(Settings::instance()->rotation());

    ui->graphicsView->setRadius(Settings::instance()->radius());

    connect(_lidar, &RPLidar::scanComplete, ui->graphicsView, &LidarGraphicsView::processRangeMap);
    connect(_lidar, &RPLidar::scanAngle, ui->graphicsView, &LidarGraphicsView::processScanAngle);

    _lidar->start();
}

LidarGuiMainWindow::~LidarGuiMainWindow()
{
    _lidar->stop();
    delete ui;
}

void LidarGuiMainWindow::onStartMotorClicked()
{
    _lidar->startMotor();
}

void LidarGuiMainWindow::onStopMotorClicked()
{
    _lidar->stopMotor();
}

void LidarGuiMainWindow::onStartScanClicked()
{
    _lidar->startScan();
}

void LidarGuiMainWindow::onStopScanClicked()
{
    _lidar->stopScan();
}

void LidarGuiMainWindow::onGetSampleRateClicked()
{
    _lidar->getSampleRate();
}

void LidarGuiMainWindow::onGetAccBoardClicked()
{

}

void LidarGuiMainWindow::onGetDeviceInfoClicked()
{

}

void LidarGuiMainWindow::onRadiusSliderChanged(int value)
{
    double radius = (double)value * .25;
    ui->textRadius->setText(QString("Scan Radius %1 meters").arg(radius));
    ui->graphicsView->setRadius(radius);
    Settings::instance()->saveRadius(radius);
}

void LidarGuiMainWindow::onRotationSliderChanged(int value)
{
    ui->textRotationAngle->setText(QString("Rotated %1%2").arg(value).arg(Unicode::specialCharacter(Unicode::Degrees)));
    _lidar->setAngleOffset(value);
    Settings::instance()->saveRotation(value);
}

void LidarGuiMainWindow::onScanSample(double bearing, double range, const QDateTime& timestamp)
{
    logText(LVL_DEBUG, QString("Sample bearing: %1  range: %2  ts: %3").arg(bearing).arg(range).arg(DateTimeUtil::toStandardString(timestamp)));
}
