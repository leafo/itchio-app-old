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
    void request(QString path, const char* slot);
    void login(QString username, QString password);

signals:
    void onLogin();
    void onLoginFailure(QString reason);

public slots:
    void getMyGamesRequest();
    void getLoginRequest();

private:
    QNetworkAccessManager* networkManager;
    QString apiKey;
    QString base;
};

#endif // ITCHIOAPI_H
