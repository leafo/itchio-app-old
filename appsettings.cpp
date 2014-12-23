#include "appsettings.h"

#include <QDebug>

AppSettings::AppSettings(const QString & fileName, Format format, QWidget* parent) :
    QSettings(fileName, format, parent)
{

}

AppSettings::~AppSettings()
{

}

QString AppSettings::loadSetting(Settings setting)
{
    return value(settingName(setting), "").toString();
}

void AppSettings::saveSetting(Settings setting, QVariant data)
{
    setValue(settingName(setting), data);
}

QString AppSettings::settingName(Settings setting)
{
    switch(setting) {
    case API_KEY:
        return "api_key";
    case USERNAME:
        return "username";
    }

    return "";
}
