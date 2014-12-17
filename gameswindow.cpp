#include <QDebug>
#include "gameswindow.h"
#include "ui_gameswindow.h"
#include "gamerow.h"

GamesWindow::GamesWindow(AppController *controller, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamesWindow),
    controller(controller)
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
    QScrollArea* scroller = ui->gameScroller;
    QWidget* wrapper = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout(wrapper);

    foreach (Game game, games) {
        qDebug() << "creating game row...";
        GameRow* gameRow = new GameRow(0, game);
        layout->addWidget(gameRow);
    }
    // scroller->setWidget(wrapper);
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
    controller->api->myGames();
}
