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

    QString loadSettings(Settings setting);
    void saveSettings(Settings setting, QVariant data);

};

#endif // SETTINGS_H
