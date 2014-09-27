#include <QDebug>
#include "gameswindow.h"
#include "ui_gameswindow.h"

GamesWindow::GamesWindow(AppController *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamesWindow),
    controller(controller),
    gamesModel(0)
{
    ui->setupUi(this);
    refreshGames();
    connect(controller->api, SIGNAL(onMyGames(QList<Game>)), this, SLOT(onMyGames(QList<Game>)));
}

GamesWindow::~GamesWindow()
{
    delete ui;
}

void GamesWindow::onMyGames(QList<Game> games)
{
    qDebug() << "got my games in games window...." << games.length();

    // TODO: what about the hanging references to games from the api?
    if (gamesModel) {
        delete gamesModel;
    }

    gamesModel = new QStringListModel(this);
    QStringList gameTitles;
    foreach (Game game, games) {
        gameTitles << game.title;
    }
    gamesModel->setStringList(gameTitles);
    ui->gameListView->setModel(gamesModel);
    ui->gameListView->setDisabled(false);
}
void GamesWindow::on_actionQuit_triggered()
{
    QCoreApplication::exit();
}

void GamesWindow::on_actionRefresh_triggered()
{
    refreshGames();
}

void GamesWindow::refreshGames()
{
    ui->gameListView->setDisabled(true);
    controller->api->myGames();
}
