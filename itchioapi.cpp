#include "itchioapi.h"
#include <QJsonDocument>
#include <QJsonObject>

ItchioApi::ItchioApi(QObject *parent) :
    QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);
    apiKey = "x3lFn558r31jiA9u7NLaviD15Bdx2ECt7A8577nN";
    base = "http://localhost.com:8080/api/1";

    // connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMyGames(QNetworkReply*)));
    // networkManager->get(QNetworkRequest(QUrl(base + "/" + apiKey + "/my-games")));
    request("my-games", SLOT(getMyGames()));
}

void ItchioApi::request(QString path, const char* slot) {
    QNetworkReply* reply = networkManager->get(QNetworkRequest(QUrl(base + "/" + apiKey + "/" + path)));
    connect(reply, SIGNAL(finished()), this, slot);
}

void ItchioApi::getMyGames() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());

    qDebug() << res.object()["games"];
    reply->deleteLater();
}

void ItchioApi::getLoginAttempt() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());

    // qDebug() << "got login attempt" << reply;
    // reply->deleteLater();
}
