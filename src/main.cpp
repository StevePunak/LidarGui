#include <QApplication>
#include <QTimer>

#include "lidarguimainwindow.h"
#include "settings.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setOrganizationName("Kanoop");
    app.setApplicationDisplayName("LIDARD Gui");
    app.setApplicationVersion(QT_STRINGIFY(LIDARGUI_VERSION));

    GuiSettings::setGlobalInstance(Settings::instance());

    LidarGuiMainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

