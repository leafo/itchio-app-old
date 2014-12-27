#include "librarywidget.h"
#include "itchioapi.h"
#include "gamerow.h"

#include <QScrollArea>

#include <QtDebug>

using itchio::LibraryWidget;

LibraryWidget::LibraryWidget(LibraryController& controller, QWidget* const parent) :
    AbstractView(controller, controller.api(), parent)
{
    connect(&model_, &Api::onMyOwnedKeys, this, &LibraryWidget::onMyOwnedKeys);
    model_.myOwnedKeys(); //TODO Give this member function a better name, e.g. requestOwnedKeys() ?
}

void LibraryWidget::onMyOwnedKeys(const QList<DownloadKey>& downloadKeys)
{
    QList<GameRow*> gameRows;
    foreach (DownloadKey key, downloadKeys) {
        gameRows << new GameRow(this, key.game, key, &controller_);
    }

    addGamesTab("My Purchases", gameRows);
}

void LibraryWidget::addGamesTab(const QString& title, const QList<GameRow*>& gameRows)
{
    //TODO Plug memory leak.
    QScrollArea* scroller = new QScrollArea();
    scroller->setObjectName("gamesScroller");

    QWidget* wrapper = new QWidget;
    wrapper->setObjectName("scrollWrapper");
    QVBoxLayout* layout = new QVBoxLayout;

    foreach (GameRow* row, gameRows) {
        layout->addWidget(row);
    }

    wrapper->setLayout(layout);
    scroller->setWidget(wrapper);

    ui_->tabWidget->addTab(scroller, title);
}
