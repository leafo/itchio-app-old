#include "librarywidget.h"
#include "ui_librarywidget.h"

#include <gameswindow.h>
#include <QScrollArea>

#include "gamerow.h"

#include <QtDebug>

LibraryWidget::LibraryWidget(QWidget *parent, AppController *controller) :
    QWidget(parent),
    ui(new Ui::LibraryWidget),
    controller(controller)
{
    ui->setupUi(this);

    connect(controller->api, SIGNAL(onMyPurchases(QList<Game>)), this, SLOT(onMyPurchases(QList<Game>)));
    controller->api->myPurchases();
}

void LibraryWidget::onMyPurchases(QList<Game> games) {
    qDebug() << "got my purchases" << games.count() ;
    addGamesTab("My Purchases", games);
}

void LibraryWidget::addGamesTab(const QString& title, QList<Game> games) {
    QScrollArea* scroller = new QScrollArea();

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
