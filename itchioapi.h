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

signals:

public slots:
    void getMyGames();
    void getLoginAttempt();

private:
    QNetworkAccessManager* networkManager;
    QString apiKey;
    QString base;
};

#endif // ITCHIOAPI_H
