#include "appsettings.h"

#include <QDebug>

#include <itchioapi.h>

AppSettings::AppSettings(const QString & fileName, Format format, QWidget* parent) :
    QSettings(fileName, format, parent)
{

}

AppSettings::~AppSettings()
{

}

QString AppSettings::loadSetting(Settings setting)
{
    return value(settingName(setting), settingDefault(setting)).toString();
}

void AppSettings::saveSetting(Settings setting, const QVariant& data)
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
    case API_URL:
        return "api_url";
    case KEEP_LOGGED_IN:
        return "keep_logged_in";
    case AUTO_UPDATE_CHECK:
        return "auto_update_check";
    case SHOW_TRAY_NOTIFICATION:
        return "display_tray_notifications";
    }

    return "";
}

QString AppSettings::settingDefault(Settings setting)
{
    switch(setting) {
    case API_KEY:
        return "";
    case USERNAME:
        return "";
    case API_URL:
        return ItchioApi::DEFAULT_API_URL;
    case KEEP_LOGGED_IN:
        return "1";
    case AUTO_UPDATE_CHECK:
        return "1";
    case SHOW_TRAY_NOTIFICATION:
        return "1";
    }

    return "";
}
