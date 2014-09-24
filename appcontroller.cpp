#include <QDebug>
#include "appcontroller.h"
#include "gameswindow.h"
#include "logindialog.h"

AppController::AppController(QObject *parent) :
    QObject(parent)
{
    api = new ItchioApi(this);
    showLogin();
}

void AppController::showGames() {
    loginDialog->hide();

    gamesWindow = new GamesWindow(this);
    gamesWindow->show();
}

void AppController::showLogin() {
    loginDialog = new LoginDialog(this);
    loginDialog->show();
}

