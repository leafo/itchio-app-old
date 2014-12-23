#include "librarywidget.h"
#include "ui_librarywidget.h"

#include <QScrollArea>

#include "gamerow.h"

#include <QtDebug>

LibraryWidget::LibraryWidget(QWidget *parent, AppController *controller) :
    QWidget(parent),
    ui(new Ui::LibraryWidget),
    controller(controller)
{
    ui->setupUi(this);

    connect(controller->api, SIGNAL(onMyOwnedKeys(QList<DownloadKey>)), this, SLOT(onMyOwnedKeys(QList<DownloadKey>)));
    controller->api->myOwnedKeys();
}

void LibraryWidget::onMyOwnedKeys(QList<DownloadKey> downloadKeys) {
    QList<Game> games;
    foreach (DownloadKey key, downloadKeys) {
        games << key.game;
    }

    addGamesTab("My Purchases", games);
}

void LibraryWidget::addGamesTab(const QString& title, QList<Game> games) {
    QScrollArea* scroller = new QScrollArea();
    scroller->setObjectName("gamesScroller");

    QWidget* wrapper = new QWidget;
    wrapper->setObjectName("scrollWrapper");
    QVBoxLayout* layout = new QVBoxLayout;

    foreach (Game game, games) {
        layout->addWidget(new GameRow(NULL, game));
    }

    wrapper->setLayout(layout);
    scroller->setWidget(wrapper);

    ui->tabWidget->addTab(scroller, title);
}


LibraryWidget::~LibraryWidget()
{
    delete ui;
}
