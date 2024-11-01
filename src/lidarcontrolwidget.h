#ifndef LIDARCONTROLWIDGET_H
#define LIDARCONTROLWIDGET_H

#include <QWidget>


class TimeSpan;
namespace Ui {
class LidarControlWidget;
}

class LidarControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LidarControlWidget(QWidget *parent = nullptr);
    ~LidarControlWidget();

    void setSampleRateNormal(const TimeSpan& value);
    void setSampleRateExpress(const TimeSpan& value);
    void setModel(int value);
    void setFirmwareVersion(const QString& value);
    void setHardwareVersion(const QString& value);
    void setSerialNumber(const QString& value);
    void setRadius(double value);
    void setRotation(double value);
    void setHealth(const QString& healthStatus, uint16_t errorCode);

private:
    Ui::LidarControlWidget *ui;

    static const double RadiusDivisor;

signals:
    void startScanClicked();
    void stopScanClicked();
    void startMotorClicked();
    void stopMotorClicked();
    void refreshSampleRateClicked();
    void refreshDeviceInfoClicked();
    void scanRadiusChanged(double radius);
    void rotationChanged(double rotation);
    void hexLogCheckChanged(bool checked);
    void performTestCode();

private slots:
    void onMotorStartStopChanged(bool value);
    void onScanStartStopChanged(bool value);
    void onRadiusSliderChanged(int value);
    void onRotationSliderChanged(int value);
};

#endif // LIDARCONTROLWIDGET_H
