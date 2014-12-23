#ifndef ITCHIOAPI_H
#define ITCHIOAPI_H

#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include "objects/game.h"
#include "objects/downloadkey.h"
#include "objects/upload.h"

class ItchioApi : public QObject
{
    Q_OBJECT

public:
    explicit ItchioApi(QObject* parent, QString apiUrl);
    void request(QString path, const char* slot);
    void loginWithPassword(QString username, QString password);
    void loginWithApiKey(QString apiKey);

    void myGames();
    void myOwnedKeys();
    void downloadKeyUploads(DownloadKey key);

    QString userKey;
    QString userName;
    int userId;

    static const char* USER_AGENT;
    static const char* DEFAULT_API_URL;

private:
    QString base;
    QNetworkAccessManager* networkManager;

signals:
    void onLogin();
    void onLoginFailure(QString reason);
    void onLoginByKeyFailure();
    void onMyGames(QList<Game> games);
    void onMyOwnedKeys(QList<DownloadKey> games);
    void onDownloadKeyUploads(DownloadKey key, QList<Upload> uploads);

public slots:
    void getMyGamesRequest();
    void getMyOwnedKeys();
    void getLoginRequest();
    void getDownloadKeyUploads();

};

#endif // ITCHIOAPI_H
