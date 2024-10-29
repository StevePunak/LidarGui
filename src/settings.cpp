#include "settings.h"

#include <QMutex>

const QString Settings::KEY_RADIUS                 = "radius";
const QString Settings::KEY_ROTATION               = "rotation";

Settings* Settings::instance()
{
    static Settings* _instance = nullptr;
    static QMutex _startLock;

    _startLock.lock();
    if(_instance == nullptr) {
        _instance = new Settings;
        _instance->ensureValidDefaults();
    }
    _startLock.unlock();
    return _instance;
}

Settings::Settings() :
    QObject(),
    GuiSettings()
{
    setGlobalInstance(this);
}

void Settings::ensureValidDefaults()
{
    int points = fontSize();
    if(points == 0) {
        setFontSize(11);
    }
}

