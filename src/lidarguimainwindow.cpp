#include "lidarguimainwindow.h"
#include "settings.h"
#include "ui_lidarguimainwindow.h"

#include <rplidarqt.h>

#include <Kanoop/datetimeutil.h>

#include <Kanoop/utility/unicode.h>

LidarGuiMainWindow::LidarGuiMainWindow(QWidget *parent) :
    MainWindowBase("lidargui", parent),
    ui(new Ui::LidarGuiMainWindow)
{
    ui->setupUi(this);

    initializeBase();

    _lidar = new RPLidar("/dev/ttyUSB3");
    _lidar->setAngleOffset(Settings::instance()->rotation());

    connect(ui->controlWidget, &LidarControlWidget::startMotorClicked, this, &LidarGuiMainWindow::onStartMotorClicked);
    connect(ui->controlWidget, &LidarControlWidget::stopMotorClicked, this, &LidarGuiMainWindow::onStopMotorClicked);
    connect(ui->controlWidget, &LidarControlWidget::startScanClicked, this, &LidarGuiMainWindow::onStartScanClicked);
    connect(ui->controlWidget, &LidarControlWidget::stopScanClicked, this, &LidarGuiMainWindow::onStopScanClicked);
    connect(ui->controlWidget, &LidarControlWidget::refreshSampleRateClicked, this, &LidarGuiMainWindow::onGetSampleRateClicked);
    connect(ui->controlWidget, &LidarControlWidget::refreshDeviceInfoClicked, this, &LidarGuiMainWindow::onGetDeviceInfoClicked);
    connect(ui->controlWidget, &LidarControlWidget::performTestCode, this, &LidarGuiMainWindow::onPerformTestCodeClicked);
    // connect(ui->controlWidget, &QPushButton::clicked, this, &LidarGuiMainWindow::onGetAccBoardClicked);

    connect(ui->controlWidget, &LidarControlWidget::scanRadiusChanged, this, &LidarGuiMainWindow::onRadiusChanged);
    connect(ui->controlWidget, &LidarControlWidget::rotationChanged, this, &LidarGuiMainWindow::onRotationSliderChanged);

    connect(ui->controlWidget, &LidarControlWidget::hexLogCheckChanged, _lidar, &RPLidar::setHexLogEnabled);

    ui->controlWidget->setRadius(Settings::instance()->radius());
    ui->controlWidget->setRotation(Settings::instance()->rotation());

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
    if(ui->controlWidget->expressScan()) {
        _lidar->startExpressScan();
    }
    else {
        _lidar->startScan();
    }
}

void LidarGuiMainWindow::onStopScanClicked()
{
    _lidar->stopScan();
}

void LidarGuiMainWindow::onGetSampleRateClicked()
{
    GetSampleRateResponse response = _lidar->getSampleRate();
    if(response.isValid()) {
        ui->controlWidget->setSampleRateNormal(response.standard());
        ui->controlWidget->setSampleRateExpress(response.express());
    }
}

void LidarGuiMainWindow::onGetAccBoardClicked()
{

}

void LidarGuiMainWindow::onGetDeviceInfoClicked()
{
    DeviceInfoResponse infoResponse = _lidar->getDeviceInfo();
    if(infoResponse.isValid()) {
        ui->controlWidget->setModel(infoResponse.model());
        ui->controlWidget->setFirmwareVersion(QString("%1.%2").arg(infoResponse.firmwareVersionMajor()).arg(infoResponse.firmwareVersionMinor()));
        ui->controlWidget->setHardwareVersion(QString::number(infoResponse.hardware()));
        ui->controlWidget->setSerialNumber(infoResponse.serialNumber());
    }

    DeviceHealthResponse healthResponse = _lidar->getDeviceHealth();
    QString health;
    if(healthResponse.isValid()) {
        switch(healthResponse.status()) {
        case DeviceHealthResponse::Ok:
            health = "OK";
            break;
        case DeviceHealthResponse::Warning:
            health = "WARNING";
            break;
        case DeviceHealthResponse::Error:
            health = "ERROR";
            break;
        default:
            break;
        }

        ui->controlWidget->setHealth(health, healthResponse.errorCode());
    }
}

void LidarGuiMainWindow::onPerformTestCodeClicked()
{
    int typical = _lidar->getTypicalScanMode();
    int scanModeCount = _lidar->getScanModeCount();
    logText(LVL_DEBUG, QString("typical: %1  count: %2").arg(typical).arg(scanModeCount));

    for(int scanMode = 0;scanMode < scanModeCount;scanMode++) {
        TimeSpan cost = _lidar->getSampleCost(scanMode);
        double maxDistance = _lidar->getMeasurementMaxDistance(scanMode);
        int answerType = _lidar->getAnswerCommandType(scanMode);
        QString name = _lidar->getScanModeName(scanMode);
        logText(LVL_DEBUG, QString("mode: %1  cost: %2  max_distance: %3  answer_type: 0x%4  name: %5")
                .arg(scanMode).arg(cost.toString(true)).arg(maxDistance)
                .arg(answerType, 0, 16).arg(name));
    }
}

void LidarGuiMainWindow::onRadiusChanged(double radius)
{
    ui->graphicsView->setRadius(radius);
    Settings::instance()->saveRadius(radius);
}

void LidarGuiMainWindow::onRotationSliderChanged(int value)
{
    _lidar->setAngleOffset(value);
    Settings::instance()->saveRotation(value);
}

void LidarGuiMainWindow::onScanSample(double bearing, double range, const QDateTime& timestamp)
{
    logText(LVL_DEBUG, QString("Sample bearing: %1  range: %2  ts: %3").arg(bearing).arg(range).arg(DateTimeUtil::toStandardString(timestamp)));
}
