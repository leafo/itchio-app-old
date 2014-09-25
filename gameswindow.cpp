#include <QDebug>
#include "gameswindow.h"
#include "ui_gameswindow.h"

GamesWindow::GamesWindow(AppController *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamesWindow),
    controller(controller)
{
    ui->setupUi(this);
    controller->api->myGames();
    connect(controller->api, SIGNAL(onMyGames(QList<Game*>)), this, SLOT(onMyGames(QList<Game*>)));
}

GamesWindow::~GamesWindow()
{
    delete ui;
}

void GamesWindow::onMyGames(QList<Game*> games)
{
    qDebug() << "got my games in games window...." << games.length();
}
