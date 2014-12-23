#ifndef ITCHIOAPI_H
#define ITCHIOAPI_H

#include <QObject>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

#include "objects/game.h"

class ItchioApi : public QObject
{
    Q_OBJECT

public:
    explicit ItchioApi(QObject* parent = 0);
    void request(QString path, const char* slot);
    void login(QString username, QString password, QString apikey = "");
    void myGames();
    void myPurchases();

    QString userKey;
    QString userName;
    int userId;

private:
    bool sentByForm;

    QString base;
    QNetworkAccessManager* networkManager;

    QJsonObject replyKey;

signals:
    void onLogin();
    void onLoginFailure(QString reason);
    void onLoginByKeyFailure();
    void onMyGames(QList<Game> games);
    void onMyPurchases(QList<Game> games);

public slots:
    void getMyGamesRequest();
    void getLoginRequest();
};

#endif // ITCHIOAPI_H
