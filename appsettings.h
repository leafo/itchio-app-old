#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>

#include "settings.h"

class AppSettings : public QSettings
{

public:
    AppSettings(const QString& fileName, Format format, QWidget* const parent = 0);
    ~AppSettings();

    QString loadSetting(Settings setting);
    void saveSetting(Settings setting, const QVariant& data);
    QString settingName(Settings setting);
    QString settingDefault(Settings setting);
};

#endif // SETTINGS_H
