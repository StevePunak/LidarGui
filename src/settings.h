#ifndef SETTINGS_H
#define SETTINGS_H

#include <Kanoop/gui/guisettings.h>

class Settings : public QObject,
                 public GuiSettings
{
    Q_OBJECT
public:
    static Settings* instance();

    Settings();

    double radius() const { return _settings.value(KEY_RADIUS).toDouble(); }
    double rotation() const { return _settings.value(KEY_ROTATION).toDouble(); }

public slots:
    void saveRadius(double value) { _settings.setValue(KEY_RADIUS, value); }
    void saveRotation(double value) { _settings.setValue(KEY_ROTATION, value); }

private:
    virtual void ensureValidDefaults() override;

    static const QString KEY_RADIUS;
    static const QString KEY_ROTATION;
};

#endif // SETTINGS_H
