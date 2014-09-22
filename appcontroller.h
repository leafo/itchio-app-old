#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <QObject>
#include "itchioapi.h"

class LoginDialog;
class GamesWindow;

class AppController : public QObject
{
    Q_OBJECT
public:
    explicit AppController(QObject *parent = 0);
    ItchioApi* api;

    void showLogin();
    void showGames();

signals:

public slots:

private:
    LoginDialog* loginDialog;
    GamesWindow* gamesWindow;
};

#endif // APPCONTROLLER_H
