#include "lidarcontrolwidget.h"
#include "ui_lidarcontrolwidget.h"

#include <Kanoop/utility/unicode.h>

#include <Kanoop/timespan.h>

const double LidarControlWidget::RadiusDivisor = .25;

LidarControlWidget::LidarControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LidarControlWidget)
{
    ui->setupUi(this);

    connect(ui->startStopMotor, &PlayPauseButton::playingChanged, this, &LidarControlWidget::onMotorStartStopChanged);
    connect(ui->startStopScan, &PlayPauseButton::playingChanged, this, &LidarControlWidget::onScanStartStopChanged);
    connect(ui->radiusSlider, &QSlider::valueChanged, this, &LidarControlWidget::onRadiusSliderChanged);
    connect(ui->rotationSlider, &QSlider::valueChanged, this, &LidarControlWidget::onRotationSliderChanged);
    connect(ui->checkHexLog, &QCheckBox::toggled, this, &LidarControlWidget::hexLogCheckChanged);
    connect(ui->pushRefreshDeviceInfo, &QToolButton::clicked, this, &LidarControlWidget::refreshDeviceInfoClicked);
    connect(ui->pushRefreshSampleRate, &QToolButton::clicked, this, &LidarControlWidget::refreshSampleRateClicked);
    connect(ui->checkExpressScan, &QCheckBox::toggled, this, &LidarControlWidget::onExpressScanToggled);
    connect(ui->pushTest, &QToolButton::clicked, this, &LidarControlWidget::performTestCode);
}

LidarControlWidget::~LidarControlWidget()
{
    delete ui;
}

void LidarControlWidget::setSampleRateNormal(const TimeSpan& value)
{
    ui->textSampleRateNormal->setText(QString("%1 ms").arg(value.totalMilliseconds()));
}

void LidarControlWidget::setSampleRateExpress(const TimeSpan& value)
{
    ui->textSampleRateExpress->setText(QString("%1 ms").arg(value.totalMilliseconds()));
}

void LidarControlWidget::setModel(int value)
{
    ui->textModel->setText(QString::number(value));
}

void LidarControlWidget::setFirmwareVersion(const QString& value)
{
    ui->textFirmwareVersion->setText(value);
}

void LidarControlWidget::setHardwareVersion(const QString& value)
{
    ui->textHardwareVersion->setText(value);
}

void LidarControlWidget::setSerialNumber(const QString& value)
{
    ui->textSerialNumber->setText(value);
}

void LidarControlWidget::setRadius(double value)
{
    value /= RadiusDivisor;
    ui->radiusSlider->setValue(value);
}

void LidarControlWidget::setRotation(double value)
{
    ui->rotationSlider->setValue(value);
}

void LidarControlWidget::setHealth(const QString& healthStatus, uint16_t errorCode)
{
    ui->textHealthStatus->setText(healthStatus);
    ui->textErrorCode->setText(QString("0x%1").arg(errorCode, 0, 16));
}

void LidarControlWidget::setExpressScan(bool value)
{
    _expressScan = value;
    ui->checkExpressScan->setChecked(value);
}

void LidarControlWidget::onMotorStartStopChanged(bool value)
{
    if(value) {
        emit startMotorClicked();
    }
    else {
        emit stopMotorClicked();
    }
}

void LidarControlWidget::onScanStartStopChanged(bool value)
{
    if(value) {
        emit startScanClicked();
    }
    else {
        emit stopScanClicked();
    }
}

void LidarControlWidget::onRadiusSliderChanged(int value)
{
    ui->textRadius->setText(QString("Scan Radius %1 meters").arg(value));
    emit scanRadiusChanged((double)value * RadiusDivisor);
}

void LidarControlWidget::onRotationSliderChanged(int value)
{
    ui->textRotationAngle->setText(QString("Rotated %1%2").arg(value).arg(Unicode::specialCharacter(Unicode::Degrees)));
    emit rotationChanged(value);
}

void LidarControlWidget::onExpressScanToggled(bool checked)
{
    _expressScan = checked;
}
