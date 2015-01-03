#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>
#include <QUrl>

#include "itchioapi.h"

const char* ItchioApi::USER_AGENT = "itch.io app 0.0";
const char* ItchioApi::DEFAULT_API_URL = "https://itch.io/api/1";

ItchioApi::ItchioApi(QObject* const parent, const QString& apiUrl)
    : QObject(parent)
    , base(apiUrl)
    , networkManager(new QNetworkAccessManager(this))
{
}

void ItchioApi::loginWithPassword(const QString& username, const QString& password, std::function<void(bool, QString)> callback)
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
    connect(reply, &QNetworkReply::finished, [=] {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            callback(false, reply->errorString());
            return;
        }

        QJsonDocument res = QJsonDocument::fromJson(reply->readAll());

        QString error = parseJsonError(res);
        if (error != "") {
            callback(false, error);
            return;
        }

        QJsonValue keyValue = res.object()["key"];
        QJsonObject keyObject = keyValue.toObject();
        userKey = keyObject["key"].toString();
        userId = keyObject["user_id"].toInt();
        qDebug() << "\nLogged in with" << userKey << userId;
        callback(true, "");
    });
}

void ItchioApi::loginWithApiKey(const QString& apiKey, std::function<void(bool, QString)> callback)
{
    userKey = apiKey;
    request("me", [=](QJsonDocument res) {
        QString error = parseJsonError(res);
        if (error != "") {
            callback(false, error);
            return;
        }

        QJsonValue userValue = res.object()["user"];
        QJsonObject userObject = userValue.toObject();

        userName = userObject["username"].toString();
        userId = userObject["id"].toInt();
        qDebug() << "\nLogged in with" << userKey << userId;
        callback(true, "");
    });
}

void ItchioApi::myGames(std::function<void(QList<Game>)> callback)
{
    request("my-games", [=](QJsonDocument res) {
        QJsonValue games = res.object()["games"];
        QList<Game> gameList;
        foreach (const QJsonValue& gameValue, games.toArray()) {
            QJsonObject gameObject = gameValue.toObject();
            gameList << Game::fromJson(gameObject);
        }

        callback(gameList);
    });
}

void ItchioApi::myOwnedKeys(std::function<void(QList<DownloadKey> keys)> callback)
{
    request("my-owned-keys", [=](QJsonDocument res) {
        QJsonValue keys = res.object()["owned_keys"];

        QList<DownloadKey> keyList;
        foreach (const QJsonValue& keyValue, keys.toArray()) {
            QJsonObject keyObject = keyValue.toObject();
            keyList <<  DownloadKey::fromJson(keyObject);
        }

        callback(keyList);
    });
}

void ItchioApi::downloadKeyUploads(const DownloadKey& key, std::function<void(QList<Upload>)> callback)
{
    request(QString("download-key/%1/uploads").arg(key.id), [=](QJsonDocument res) {
        QJsonValue uploadsValue = res.object()["uploads"];

        QList<Upload> uploads;
        foreach (const QJsonValue& uploadValue, uploadsValue.toArray()) {
            QJsonObject uploadObject = uploadValue.toObject();
            uploads << Upload::fromJson(uploadObject);
        }

        callback(uploads);
    });
}

void ItchioApi::downloadUpload(const DownloadKey& key, const Upload& upload, std::function<void(QString)> callback)
{
    request(QString("download-key/%1/download/%2").arg(key.id).arg(upload.id), [=](QJsonDocument res) {
        QJsonValue urlValue = res.object()["url"];
        QString url = urlValue.toString();
        callback(url);
    });
}

QString ItchioApi::parseJsonError(const QJsonDocument& document)
{
    QJsonValue errors = document.object()["errors"];
    if (!errors.isNull()) {
        return errors.toArray()[0].toString();
    }

    return "";
}

void ItchioApi::request(const QString& path, std::function<void(QJsonDocument)> callback)
{
    QString url = base + "/" + userKey + "/" + path;
    qDebug() << "Requesting URL" << url;

    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::UserAgentHeader, USER_AGENT);

    QNetworkReply* const reply = networkManager->get(request);

    connect(reply, &QNetworkReply::finished, [=] {
        reply->deleteLater();
        if (reply->error() == QNetworkReply::NoError) {
            callback(QJsonDocument::fromJson(reply->readAll()));
            return;
        }

        // TODO: send some sort of error signal
        qFatal("Failed to get response from server");
    });
}
