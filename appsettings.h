#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>
#include <QByteArray>
#include <QSize>
#include <QPoint>

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

    bool showLibraryUpdateNotifications() const;
    void enableLibraryUpdateNotifications(const bool enable);

    bool showDownloadFinishedNotifications() const;
    void enableDownloadFinishedNotifications(const bool enable);

    bool showGameUpdateAvailableNotifications() const;
    void enableGameUpdateAvailableNotifications(const bool enable);

    bool startMaximized() const;
    void enableStartMaximized(const bool enable);

    QByteArray windowGeometry() const;
    void setWindowGeometry(const QByteArray geometry);

    QSize windowOldSize() const;
    void setWindowOldSize(const QSize size);

    QPoint windowOldPosition() const;
    void setWindowOldPosition(const QPoint position);

private:
    enum class Key {
        API_KEY,
        API_URL,
        USERNAME,
        AUTO_LOGIN,
        AUTO_UPDATE_CHECKS,
        SHOW_TRAY_NOTIFICATIONS,
        SHOW_LIBRARY_UPDATE_NOTIFICATIONS,
        SHOW_GAME_UPDATE_AVAILABLE_NOTIFICATIONS,
        SHOW_DOWNLOAD_FINISHED_NOTIFICATIONS,
        START_MAXIMIZED,
        WINDOW_GEOMETRY,
        WINDOW_OLD_SIZE,
        WINDOW_OLD_POSITION
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
    constexpr static const bool DEFAULT_SHOW_LIBRARY_UPDATE_AVAILABLE_NOTIFICATIONS = true;
    constexpr static const bool DEFAULT_SHOW_DOWNLOAD_FINISHED_NOTIFICATIONS = true;
    constexpr static const bool DEFAULT_SHOW_GAME_UPDATE_AVAILABLE_NOTIFICATIONS = true;
    constexpr static const bool DEFAULT_AUTO_UPDATE_CHECKS = true;
};

#endif // APPSETTINGS_H

//} // namespace itchio
