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

namespace itchio {

class Api : public QObject
{
    Q_OBJECT

public:
    explicit Api(const QString& apiUrl);

    void request(const QString& path, const char* slot);
    void loginWithPassword(const QString& username, const QString& password);
    void loginWithApiKey(const QString& apiKey);

    void myGames();
    void myOwnedKeys();
    void downloadKeyUploads(const DownloadKey& key);

    QString userKey;
    QString userName;
    int userId;

    static const char* USER_AGENT;
    static const char* DEFAULT_API_URL;

private:
    const QString base;
    QNetworkAccessManager* const networkManager;

signals:
    void onLogin();
    void onLoginFailure(QString reason);
    void onMyGames(QList<Game> games);
    void onMyOwnedKeys(QList<DownloadKey> games);
    void onDownloadKeyUploads(DownloadKey key, QList<Upload> uploads);

public slots:
    void getMyGamesRequest();
    void getMyOwnedKeys();
    void getLoginRequest();
    void getDownloadKeyUploads();
};

} // namespace itchio

#endif // ITCHIOAPI_H
