#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QUrl>

#include "itchioapi.h"

const char* ItchioApi::USER_AGENT =  "itch.io app 0.0";
const char* ItchioApi::DEFAULT_API_URL = "https://itch.io/api/1";

ItchioApi::ItchioApi(QObject* const parent, const QString& apiUrl) :
    QObject(parent),
    base(apiUrl),
    networkManager(new QNetworkAccessManager(this))
{}

void ItchioApi::loginWithPassword(const QString& username, const QString& password)
{
    userName = username;

    QUrlQuery params;
    QNetworkRequest request;

    params.addQueryItem("username", username);
    params.addQueryItem("password", password);
    params.addQueryItem("source", "desktop");

    request.setUrl(QUrl(base + "/login"));

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    QByteArray paramBytes;
    paramBytes.append(params.toString());

    QNetworkReply* const reply = networkManager->post(request, paramBytes);
    connect(reply, SIGNAL(finished()), this, SLOT(getLoginRequest()));
}

void ItchioApi::loginWithApiKey(const QString& apiKey)
{
    userKey = apiKey;
    request("me", SLOT(getLoginRequest()));
}

void ItchioApi::myGames()
{
    request("my-games", SLOT(getMyGamesRequest()));
}

void ItchioApi::myOwnedKeys()
{
    request("my-owned-keys", SLOT(getMyOwnedKeys()));
}

void ItchioApi::downloadKeyUploads(const DownloadKey& key)
{
    request(QString("download-key/%1/uploads").arg(key.id), SLOT(getDownloadKeyUploads()));
}

void ItchioApi::request(const QString& path, const char* slot)
{
    QString url =  base + "/" + userKey + "/" + path;
    qDebug() << "Requesting URL" << url;

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    QNetworkReply* const reply = networkManager->get(request);
    connect(reply, SIGNAL(finished()), this, slot);
}

void ItchioApi::getMyGamesRequest()
{
    QNetworkReply* const reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());
    QJsonValue games = res.object()["games"];
    QList<Game> gameList;
    foreach (const QJsonValue& gameValue, games.toArray()) {
        QJsonObject gameObject = gameValue.toObject();
        gameList << Game::fromJson(gameObject);
    }

    qDebug() << "sending" << gameList.length() << "games";
    onMyGames(gameList);
}

void ItchioApi::getMyOwnedKeys()
{
    QNetworkReply* const reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());
    QJsonValue keys = res.object()["owned_keys"];

    QList<DownloadKey> keyList;
    foreach (const QJsonValue& keyValue, keys.toArray()) {
        QJsonObject keyObject = keyValue.toObject();
        keyList <<  DownloadKey::fromJson(keyObject);
    }

    onMyOwnedKeys(keyList);
}

void ItchioApi::getLoginRequest()
{
    QNetworkReply* const reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        onLoginFailure("Failed to connect to itch.io");
        return;
    }

    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());
    //qDebug() << res;

    QJsonValue errors = res.object()["errors"];

    if (!errors.isNull()) {
        QString error = errors.toArray()[0].toString();

        onLoginFailure(error);

        return;
    }

    QJsonValue keyValue;

    if(userKey == "") {
        keyValue = res.object()["key"];

        if (!keyValue.isNull()) {
            QJsonObject key = keyValue.toObject();
            userKey = key["key"].toString();
            userId = key["user_id"].toInt();
            qDebug() << "\nLogged in with" << userKey << userId;

            onLogin();
            return;
        }
    } else {
        keyValue = res.object()["user"];

        if (!keyValue.isNull()) {
            QJsonObject key = keyValue.toObject();
            userName = key["username"].toString();
            userId = key["id"].toInt();
            qDebug() << "\nLogged in with" << userKey << userId;
            onLogin();
            return;
        }
    }
}

void ItchioApi::getDownloadKeyUploads()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());


    QJsonValue uploads = res.object()["uploads"];

    QList<Upload> uploadList;
    foreach (const QJsonValue& uploadValue, uploads.toArray()) {
        QJsonObject uploadObject = uploadValue.toObject();
        uploadList << Upload::fromJson(uploadObject);
    }

    onDownloadKeyUploads(DownloadKey(), uploadList);
}
