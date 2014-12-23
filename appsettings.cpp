#include "appsettings.h"

#include <QDebug>

AppSettings::AppSettings(const QString & fileName, Format format, QWidget* parent) :
    QSettings(fileName, format, parent)
{

}

AppSettings::~AppSettings()
{

}

QString AppSettings::loadSettings(Settings setting)
{
    switch(setting){
        case API_KEY:
            return value("API_KEY", "").toString();
            break;
        case USERNAME:
            return value("USERNAME", "").toString();
            break;
    }

    return "";
}

void AppSettings::saveSettings(Settings setting, QVariant data)
{
    switch(setting){
        case API_KEY:
            setValue("API_KEY", data);
            break;
        case USERNAME:
            setValue("USERNAME", data);
            break;
    }
}
