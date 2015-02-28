#ifndef ITCHIOAPI_H
#define ITCHIOAPI_H

#include <functional>


#include <QObject>
#include <QNetworkAccessManager>
#include <QJsonDocument>

#include "objects/game.h"
#include "objects/downloadkey.h"
#include "objects/upload.h"

class ItchioApi : public QObject
{
    Q_OBJECT

public:
    explicit ItchioApi(QObject* const parent, const QString& apiUrl);

    void request(const QString& path, std::function<void (QJsonDocument)> callback);
    void loginWithPassword(const QString& username, const QString& password, std::function<void (bool, QString)> callback);
    void loginWithApiKey(const QString& apiKey, std::function<void (bool, QString)> callback);

    void myGames(std::function<void (QList<Game>)> callback);
    void myOwnedKeys(std::function<void (QList<DownloadKey>)> callback);
    void myClaimedKeys(std::function<void (QList<DownloadKey>)> callback);

    void downloadKeyUploads(const DownloadKey& key, std::function<void (QList<Upload>)> callback);
    void downloadUpload(const DownloadKey& key, const Upload& upload, std::function<void (QString)> callback);

    QString userKey;
    QString userName;
    int userId;

    static const char* USER_AGENT;
    static const char* DEFAULT_API_URL;

private:
    const QString base;
    QNetworkAccessManager* const networkManager;
    QString parseJsonError(const QJsonDocument& document);

};

#endif // ITCHIOAPI_H
