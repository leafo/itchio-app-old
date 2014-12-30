#include "appsettings.h"
#include "itchioapi.h"

//using itchio::AppSettings;

AppSettings::AppSettings(const QString& filename, const Format format, QObject* const parent) :
    QSettings(filename, format, parent)
{
}

QString AppSettings::apiKey() const
{
    return value(Key::API_KEY).toString();
}

void AppSettings::setApiKey(const QString& key)
{
    setValue(Key::API_KEY, key);
}

bool AppSettings::hasValidApiKey() const
{
    //TODO Perform a more thorough check.
    return apiKey() != "";
}

QString AppSettings::apiUrl() const
{
    return value(Key::API_URL, ItchioApi::DEFAULT_API_URL).toString();
}

void AppSettings::setApiUrl(const QString& url)
{
    setValue(Key::API_URL, url);
}

QString AppSettings::username() const
{
    return value(Key::USERNAME).toString();
}

void AppSettings::setUsername(const QString& username)
{
    setValue(Key::USERNAME, username);
}

bool AppSettings::autoLogin() const
{
    return value(Key::AUTO_LOGIN, AppSettings::DEFAULT_AUTO_LOGIN).toBool();
}

void AppSettings::enableAutoLogin(const bool enable)
{
    setValue(Key::AUTO_LOGIN, enable);
}

bool AppSettings::autoUpdateChecks() const
{
    return value(Key::AUTO_UPDATE_CHECKS, AppSettings::DEFAULT_AUTO_UPDATE_CHECKS).toBool();
}

void AppSettings::enableAutoUpdateChecks(const bool enable)
{
    setValue(Key::AUTO_UPDATE_CHECKS, enable);
}

bool AppSettings::showTrayNotifications() const
{
    return value(Key::SHOW_TRAY_NOTIFICATIONS, AppSettings::DEFAULT_SHOW_TRAY_NOTIFICATIONS).toBool();
}

void AppSettings::enableTrayNotifications(const bool enable)
{
    setValue(Key::SHOW_TRAY_NOTIFICATIONS, enable);
}

QString AppSettings::toString(const Key& key)
{
    switch (key) {
    case Key::API_KEY:
        return "api_key";
    case Key::API_URL:
        return "api_url";
    case Key::USERNAME:
        return "username";
    case Key::AUTO_LOGIN:
        return "auto_login";
    case Key::AUTO_UPDATE_CHECKS:
        return "auto_update_checks";
    case Key::SHOW_TRAY_NOTIFICATIONS:
        return "show_tray_notifications";
    default:
        // This is a guard to make sure any keys added later on are handled in this switch-case.
        qFatal("[AppSettings::toString] Undefined key!");
    }
}
