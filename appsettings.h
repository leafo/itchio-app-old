#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSettings>
#include <QVariant>

#include "settings.h"

class AppSettings : public QSettings
{

public:
    AppSettings(const QString & fileName, Format format, QWidget* parent = 0);
    ~AppSettings();

    QString loadSetting(Settings setting);
    void saveSetting(Settings setting, QVariant data);
    QString settingName(Settings setting);
    QString settingDefault(Settings setting);
};

#endif // SETTINGS_H
