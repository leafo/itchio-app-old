#include "itchioapi.h"
#include <QJsonDocument>
#include <QJsonObject>

ItchioApi::ItchioApi(QObject *parent) :
    QObject(parent)
{
    networkManager = new QNetworkAccessManager(this);

    QString apiKey = "x3lFn558r31jiA9u7NLaviD15Bdx2ECt7A8577nN";
    QString base = "http://localhost.com:8080/api/1";

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(getMyGames(QNetworkReply*)));
    networkManager->get(QNetworkRequest(QUrl(base + "/" + apiKey + "/my-games")));
}

void ItchioApi::getMyGames(QNetworkReply* reply) {
    QJsonDocument res = QJsonDocument::fromJson(reply->readAll());
    qDebug() << res.object()["games"];
    reply->deleteLater();
}


void ItchioApi::getLoginAttempt(QNetworkReply* reply) {
    qDebug() << "got login attempt" << reply;
    reply->deleteLater();
}
