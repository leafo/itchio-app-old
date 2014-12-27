#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

namespace itchio {

class Settings : public QSettings
{
public:
    explicit Settings(const QString& filename);

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
        QSettings::setValue(Settings::toString(key), value);
    }

    inline QVariant value(const Key& key) const
    {
        return QSettings::value(Settings::toString(key));
    }

    inline bool contains(const Key& key) const
    {
        return QSettings::contains(Settings::toString(key));
    }
};

} // namespace itchio

#endif // SETTINGS_H
