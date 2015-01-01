#ifndef ITCHIOAPI_H
#define ITCHIOAPI_H

#include <QObject>
#include <QNetworkAccessManager>

#include "objects/game.h"
#include "objects/downloadkey.h"
#include "objects/upload.h"

class ItchioApi : public QObject
{
    Q_OBJECT

public:
    explicit ItchioApi(QObject* const parent, const QString& apiUrl);

    void request(const QString& path, const char* slot);
    void loginWithPassword(const QString& username, const QString& password);
    void loginWithApiKey(const QString& apiKey);

    void myGames();
    void myOwnedKeys();
    void downloadKeyUploads(const DownloadKey& key);
    void downloadUpload(const DownloadKey& key, const Upload& upload);

    QString userKey;
    QString userName;
    int userId;

    static const char* USER_AGENT;
    static const char* DEFAULT_API_URL;

private:
    const QString base;
    QNetworkAccessManager* const networkManager;
    QNetworkReply* sendRequest(const QString& path);
    QJsonDocument parseAndCloseReply(QNetworkReply* const reply);

signals:
    void onLogin();
    void onLoginFailure(QString reason);
    void onMyGames(QList<Game> games);
    void onMyOwnedKeys(QList<DownloadKey> games);
    void onDownloadKeyUploads(DownloadKey key, QList<Upload> uploads);
    void onUploadDownload(Upload upload, QString url);

public slots:
    void getMyGamesRequest();
    void getMyOwnedKeys();
    void getLoginRequest();
    void getDownload();

};

#endif // ITCHIOAPI_H
