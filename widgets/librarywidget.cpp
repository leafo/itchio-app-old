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

    tabGameFrames << new QList<GameFrame*> << new QList<GameFrame*>;

    tabScrollAreas << new QScrollArea() << new QScrollArea();
    tabWrappers << new QWidget << new QWidget;
    tabLayouts << new QVBoxLayout() << new QVBoxLayout();
    tabRowLayouts << new QList<QVBoxLayout*> << new QList<QVBoxLayout*>;
    tabColLayouts << new QList<QHBoxLayout*> << new QList<QHBoxLayout*>;

    for(int i = 0; i < tabScrollAreas.size(); i++){
        tabScrollAreas.at(i)->setObjectName("gamesScroller");
        tabWrappers.at(i)->setObjectName("scrollWrapper");
    }

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

    tabGameFrames.at(0)->append(gameFrames);
    addGamesTab("Purchased", 0);

}

void LibraryWidget::onMyClaimedKeys(QList<DownloadKey> downloadKeys)
{
    QList<GameFrame*> gameFrames;

    foreach (DownloadKey key, downloadKeys) {
        gameFrames << new GameFrame(this, key.game, key, controller);
    }

    tabGameFrames.at(1)->append(gameFrames);
    addGamesTab("Claimed", 1);
}

void LibraryWidget::addGamesTab(const QString& title, int tab)
{
    tabRowLayouts.at(tab)->append(new QVBoxLayout);
    tabColLayouts.at(tab)->append(new QHBoxLayout);

    tabLayouts.at(tab)->addLayout(tabRowLayouts.at(tab)->at(0));
    tabRowLayouts.at(tab)->at(0)->addLayout(tabColLayouts.at(tab)->at(0));

    maxGamesFramesPerRow = (ui->tabWidget->width() - 80) / gameFrameWidth;
    int i = 1;
    int j = 0;

    while(i < tabGameFrames.at(tab)->size() + 1) {
        tabColLayouts.at(tab)->at(j)->addWidget(tabGameFrames.at(tab)->at(i - 1));

        if(i % maxGamesFramesPerRow == 0) {
            tabColLayouts.at(tab)->append(new QHBoxLayout);

            j++;

            tabRowLayouts.at(tab)->at(0)->addLayout(tabColLayouts.at(tab)->at(j));
        }

        i++;
    }

    int p = maxGamesFramesPerRow - (tabGameFrames.at(tab)->size() % maxGamesFramesPerRow);

    while(p > 0) {
        tabColLayouts.at(tab)->at(j)->addSpacerItem(new QSpacerItem(gameFrameWidth, 0));

        p--;
    }

    tabWrappers.at(tab)->setLayout(tabLayouts.at(tab));
    tabScrollAreas.at(tab)->setWidget(tabWrappers.at(tab));

    ui->tabWidget->addTab(tabScrollAreas.at(tab), title);

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
    if((ui->tabWidget->width() - 80) / gameFrameWidth != maxGamesFramesPerRow){
        maxGamesFramesPerRow = (ui->tabWidget->width() - 80) / gameFrameWidth;

        tabWrappers.clear();
        tabLayouts.clear();

        for(int i = 0; i < tabScrollAreas.size(); i++){
            tabRowLayouts.at(i)->clear();
            tabColLayouts.at(i)->clear();
        }

        tabWrappers << new QWidget << new QWidget;
        tabLayouts << new QVBoxLayout() << new QVBoxLayout();
        tabRowLayouts << new QList<QVBoxLayout*> << new QList<QVBoxLayout*>;
        tabColLayouts << new QList<QHBoxLayout*> << new QList<QHBoxLayout*>;

        for(int k = 0; k < tabScrollAreas.size(); k++){
            tabWrappers.at(k)->setObjectName("scrollWrapper");

            tabRowLayouts.at(k)->append(new QVBoxLayout);
            tabColLayouts.at(k)->append(new QHBoxLayout);

            tabLayouts.at(k)->addLayout(tabRowLayouts.at(k)->at(0));
            tabRowLayouts.at(k)->at(0)->addLayout(tabColLayouts.at(k)->at(0));

            int i = 1;
            int j = 0;

            while(i < tabGameFrames.at(k)->size() + 1) {
                tabColLayouts.at(k)->at(j)->addWidget(tabGameFrames.at(k)->at(i - 1));

                if(i % maxGamesFramesPerRow == 0) {
                    tabColLayouts.at(k)->append(new QHBoxLayout);

                    j++;

                    tabRowLayouts.at(k)->at(0)->addLayout(tabColLayouts.at(k)->at(j));
                }

                i++;
            }

            int p = maxGamesFramesPerRow - (tabGameFrames.at(k)->size() % maxGamesFramesPerRow);
            while(p > 0) {
                tabColLayouts.at(k)->at(j)->addSpacerItem(new QSpacerItem(gameFrameWidth, 0));

                p--;
            }


            tabWrappers.at(k)->setLayout(tabLayouts.at(k));
            tabScrollAreas.at(k)->setWidget(tabWrappers.at(k));
        }
    }
}

LibraryWidget::~LibraryWidget()
{
    delete ui;
}
