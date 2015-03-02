#include <QScrollArea>

#include <QtDebug>

#include "librarywidget.h"
#include "ui_librarywidget.h"

LibraryWidget::LibraryWidget(QWidget* const parent, AppController* const controller)
    : QWidget(parent)
    , ui(new Ui::LibraryWidget)
    , controller(controller)
{
    ui->setupUi(this);

    controller->api->myOwnedKeys([this](QList<DownloadKey> keys) {
        onMyPurchasedKeys(keys);
    });

    controller->api->myClaimedKeys([this](QList<DownloadKey> keys) {
        onMyClaimedKeys(keys);
    });
}

void LibraryWidget::onMyPurchasedKeys(QList<DownloadKey> downloadKeys)
{
    QList<GameRow*> gameRows;
    foreach (DownloadKey key, downloadKeys) {
        gameRows << new GameRow(this, key.game, key, controller);
    }

    addGamesTab("My Purchases", gameRows);
}

void LibraryWidget::onMyClaimedKeys(QList<DownloadKey> downloadKeys)
{
    QList<GameRow*> gameRows;
    foreach (DownloadKey key, downloadKeys) {
        gameRows << new GameRow(this, key.game, key, controller);
    }

    addGamesTab("My Claimed Games", gameRows);
}

void LibraryWidget::addGamesTab(const QString& title, const QList<GameRow*>& gameRows)
{
    QScrollArea* scroller = new QScrollArea();
    scroller->setObjectName("gamesScroller");

    QWidget* wrapper = new QWidget;
    wrapper->setObjectName("scrollWrapper");
    QHBoxLayout* layout = new QHBoxLayout;

    foreach (GameRow* row, gameRows) {
        layout->addWidget(row);
    }

    wrapper->setLayout(layout);
    scroller->setWidget(wrapper);

    ui->tabWidget->addTab(scroller, title);
}

LibraryWidget::~LibraryWidget()
{
    delete ui;
}
