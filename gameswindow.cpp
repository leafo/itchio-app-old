#include <QDebug>
#include "gameswindow.h"
#include "ui_gameswindow.h"
#include "gamerow.h"

#include <QPushButton>

GamesWindow::GamesWindow(QWidget *parent, AppController *controller) :
    QMainWindow(parent),
    ui(new Ui::GamesWindow),
    controller(controller)
{
    setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint );

    ui->setupUi(this);
    refreshGames();
    connect(controller->api, SIGNAL(onMyGames(QList<Game>)), this, SLOT(onMyGames(QList<Game>)));
    connect(controller->api, SIGNAL(onMyPurchases(QList<Game>)), this, SLOT(onMyPurchases(QList<Game>)));
}

GamesWindow::~GamesWindow()
{
    delete ui;
}

void GamesWindow::onMyGames(QList<Game> games)
{
    qDebug() << "got my games in games window...." << games.length();
    QScrollArea* scroller = ui->myGameScroller;
    QWidget* wrapper = new QWidget;
    wrapper->setObjectName("scrollWrapper");
    QVBoxLayout* layout = new QVBoxLayout;

    foreach (Game game, games) {
        layout->addWidget(new GameRow(NULL, game));
    }

    wrapper->setLayout(layout);
    scroller->setWidget(wrapper);
}

void GamesWindow::onMyPurchases(QList<Game> games)
{
    QScrollArea* scroller = ui->myPurchasesScroller;
    QWidget* wrapper = new QWidget;
    wrapper->setObjectName("scrollWrapper");
    QVBoxLayout* layout = new QVBoxLayout;

    foreach (Game game, games) {
        layout->addWidget(new GameRow(NULL, game));
    }

    wrapper->setLayout(layout);
    scroller->setWidget(wrapper);
}

void GamesWindow::on_actionQuit_triggered()
{
    controller->hide();
}

void GamesWindow::on_actionRefresh_triggered()
{
    refreshGames();
}

void GamesWindow::refreshGames()
{
    controller->api->myGames();
    controller->api->myPurchases();
}

void GamesWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    controller->hide();
}
