#include <QScrollArea>
#include <QSizePolicy>
#include <QSpacerItem>

#include <QtDebug>

#include "librarywidget.h"
#include "ui_librarywidget.h"

LibraryWidget::LibraryWidget(QWidget* const parent, AppController* const controller)
    : QWidget(parent)
    , ui(new Ui::LibraryWidget)
    , controller(controller)
{
    ui->setupUi(this);

    tabLayouts << new QVBoxLayout() << new QVBoxLayout();
    tabRowLayouts << new QList<QVBoxLayout*> << new QList<QVBoxLayout*>;
    tabColLayouts << new QList<QHBoxLayout*> << new QList<QHBoxLayout*>;
    tabWidgets << new QList<GameFrame*> << new QList<GameFrame*>;

    controller->api->myOwnedKeys([this](QList<DownloadKey> keys) {
        onMyPurchasedKeys(keys);
    });

    controller->api->myClaimedKeys([this](QList<DownloadKey> keys) {
        onMyClaimedKeys(keys);
    });
}

void LibraryWidget::onMyPurchasedKeys(QList<DownloadKey> downloadKeys)
{
    QList<GameFrame*> gameFrames;

    foreach (DownloadKey key, downloadKeys) {
        gameFrames << new GameFrame(this, key.game, key, controller);
    }

    addGamesTab("Purchased", gameFrames, 0);
}

void LibraryWidget::onMyClaimedKeys(QList<DownloadKey> downloadKeys)
{
    QList<GameFrame*> gameFrames;

    foreach (DownloadKey key, downloadKeys) {
        gameFrames << new GameFrame(this, key.game, key, controller);
    }

    addGamesTab("Claimed", gameFrames, 1);
}

void LibraryWidget::addGamesTab(const QString& title, const QList<GameFrame*>& gameFrames, int tab)
{
    gameFrameWidth = gameFrames.at(0)->width();

    tabWidgets.at(tab)->append(gameFrames);

    QScrollArea* scroller = new QScrollArea();
    scroller->setObjectName("gamesScroller");

    QWidget* wrapper = new QWidget;
    wrapper->setObjectName("scrollWrapper");

    tabRowLayouts.at(tab)->append(new QVBoxLayout);
    tabColLayouts.at(tab)->append(new QHBoxLayout);

    tabLayouts.at(tab)->addLayout(tabRowLayouts.at(tab)->at(0));
    tabRowLayouts.at(tab)->at(0)->addLayout(tabColLayouts.at(tab)->at(0));

    int c = (ui->tabWidget->width() / gameFrameWidth) - 1;
    int i = 1;
    int j = 0;

    while(true) {
        tabColLayouts.at(tab)->at(j)->addWidget(gameFrames.at(i - 1));

        if(i % c == 0) {
            tabColLayouts.at(tab)->append(new QHBoxLayout);

            j++;

            tabRowLayouts.at(tab)->at(0)->addLayout(tabColLayouts.at(tab)->at(j));
        }

        if(i == gameFrames.size()) {

            while(i % c != 0) {
                tabColLayouts.at(tab)->at(j)->addSpacerItem(new QSpacerItem(gameFrameWidth + 15, 0));

                i++;
            }

            break;
        }

        i++;
    }

    wrapper->setLayout(tabLayouts.at(tab));
    scroller->setWidget(wrapper);

    ui->tabWidget->addTab(scroller, title);

    tabSetupCount++;
}

void LibraryWidget::resizeEvent(QResizeEvent *event)
{
    event->accept();

    if(tabSetupCount == 2) {
        adjustTabLayouts();
    }
}

void LibraryWidget::adjustTabLayouts()
{
    int c = (ui->tabWidget->width() / gameFrameWidth) - 1;
}

LibraryWidget::~LibraryWidget()
{
    delete ui;
}
