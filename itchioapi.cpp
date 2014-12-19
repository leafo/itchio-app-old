#include "itchioapi.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QUrlQuery>

ItchioApi::ItchioApi(QObject *parent) :
    QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    base = "http://itch.io/api/1";

    // connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMyGames(QNetworkReply*)));
    // networkManager->get(QNetworkRequest(QUrl(base + "/" + apiKey + "/my-games")));
    // request("my-games", SLOT(getMyGamesRequest()));
}

void ItchioApi::login(QString username, QString password) {
    QUrlQuery params;
    params.addQueryItem("username", username);
    params.addQueryItem("password", password);
    params.addQueryItem("source", "desktop");

    QNetworkRequest request(QUrl(base + "/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    QByteArray paramBytes;
    paramBytes.append(params.toString());
    QNetworkReply* reply = networkManager->post(request, paramBytes);
    connect(reply, SIGNAL(finished()), this, SLOT(getLoginRequest()));
}

void ItchioApi::myGames()
{
    request("my-games", SLOT(getMyGamesRequest()));
}

void ItchioApi::request(QString path, const char* slot) {
    QString url =  base + "/" + apiKey + "/" + path;
    qDebug() << "Requesting URL" << url;
    QNetworkReply* reply = networkManager->get(QNetworkRequest(QUrl(url)));
    connect(reply, SIGNAL(finished()), this, slot);
}

void ItchioApi::getMyGamesRequest() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
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

void ItchioApi::getLoginRequest() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        onLoginFailure("Failed to connect to itch.io");
        return;
    }

    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());
    QJsonValue errors = res.object()["errors"];

    if (!errors.isNull()) {
        QString error = errors.toArray()[0].toString();
        onLoginFailure(error);
        return;
    }

    QJsonValue keyValue = res.object()["key"];

    if (!keyValue.isNull()) {
        QJsonObject key = keyValue.toObject();
        apiKey = key["key"].toString();
        userId = key["user_id"].toInt();
        qDebug() << "Logged in with" << apiKey << userId;
        onLogin();
        return;
    }

    qDebug() << res;
}
