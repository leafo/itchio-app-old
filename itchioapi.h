#ifndef ITCHIOAPI_H
#define ITCHIOAPI_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class ItchioApi : public QObject
{
    Q_OBJECT
public:
    explicit ItchioApi(QObject* parent = 0);

signals:

public slots:
    void getMyGames(QNetworkReply* reply);
    void getLoginAttempt(QNetworkReply* reply);

private:
    QNetworkAccessManager* networkManager;

};

#endif // ITCHIOAPI_H
