#ifndef LIDARGUIMAINWINDOW_H
#define LIDARGUIMAINWINDOW_H

#include <Kanoop/gui/mainwindowbase.h>


class RPLidar;
namespace Ui {
class LidarGuiMainWindow;
}

class LidarGuiMainWindow : public MainWindowBase
{
    Q_OBJECT

public:
    explicit LidarGuiMainWindow(QWidget *parent = nullptr);
    ~LidarGuiMainWindow();

private:
    Ui::LidarGuiMainWindow *ui;

    RPLidar* _lidar;

private slots:
    void onStartMotorClicked();
    void onStopMotorClicked();
    void onStartScanClicked();
    void onStopScanClicked();
    void onGetSampleRateClicked();
    void onGetAccBoardClicked();
    void onGetDeviceInfoClicked();
    void onPerformTestCodeClicked();

    void onRadiusChanged(double radius);
    void onRotationSliderChanged(int value);

    void onScanSample(double bearing, double range, const QDateTime& timestamp);

};

#endif // LIDARGUIMAINWINDOW_H
