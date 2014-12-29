#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

//namespace itchio {

class AppSettings : public QSettings
{
public:
    AppSettings(const QString& fileName, const Format fileFormat, QObject* const parent = nullptr);

    QString apiKey() const;
    void setApiKey(const QString& key);
    bool hasValidApiKey() const;

    QString apiUrl() const;
    void setApiUrl(const QString& url);

    QString username() const;
    void setUsername(const QString& username);

    bool autoLogin() const;
    void enableAutoLogin(const bool enable);

    bool autoUpdateChecks() const;
    void enableAutoUpdateChecks(const bool enable);

    bool showTrayNotifications() const;
    void enableTrayNotifications(const bool enable);

private:
    enum class Key
    {
        API_KEY,
        API_URL,
        USERNAME,
        AUTO_LOGIN,
        AUTO_UPDATE_CHECKS,
        SHOW_TRAY_NOTIFICATIONS
    };

    static QString toString(const Key& key);

    inline void setValue(const Key& key, const QVariant& value)
    {
        QSettings::setValue(AppSettings::toString(key), value);
    }

    inline QVariant value(const Key& key, const QVariant& defaultValue = QVariant()) const
    {
        return QSettings::value(AppSettings::toString(key), defaultValue);
    }

    constexpr static const bool DEFAULT_AUTO_LOGIN = true;
    constexpr static const bool DEFAULT_SHOW_TRAY_NOTIFICATIONS = true;
    constexpr static const bool DEFAULT_AUTO_UPDATE_CHECKS = true;
};

#endif // APPSETTINGS_H

//} // namespace itchio
