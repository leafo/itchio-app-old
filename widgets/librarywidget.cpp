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
        tabScrollAreas.at(i)->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    }

    controller->api->myOwnedKeys([this](QList<DownloadKey> keys) {
        onMyPurchasedKeys(keys);
    });

    controller->api->myClaimedKeys([this](QList<DownloadKey> keys) {
        onMyClaimedKeys(keys);
    });

    updateTimer = new QTimer(this);

    connect(updateTimer, &QTimer::timeout, this, &LibraryWidget::onUpdate);
    updateTimer->start(60000);
}

void LibraryWidget::onMyPurchasedKeys(QList<DownloadKey> downloadKeys)
{
    QList<GameFrame*> gameFrames;

    int repeatCount = 0;

    foreach (DownloadKey key, downloadKeys) {
        for(int i = 0; i < tabGameFrames.at(0)->size(); i++){
            if(key.game.id == tabGameFrames.at(0)->at(i)->game.id){
                repeatCount++;
            }
        }

        if(repeatCount == 0){
            gameFrames << new GameFrame(this, key.game, key, controller);
        }
    }

    if(!gameFrames.isEmpty()){
        tabGameFrames.at(0)->append(gameFrames);
    }
    if(tabSetupCount < 2){
        addGamesTab("Purchased", 0);
    }
}

void LibraryWidget::onMyClaimedKeys(QList<DownloadKey> downloadKeys)
{
    QList<GameFrame*> gameFrames;

    int repeatCount = 0;

    foreach (DownloadKey key, downloadKeys) {
        for(int i = 0; i < tabGameFrames.at(1)->size(); i++){
            if(key.game.id == tabGameFrames.at(1)->at(i)->game.id){
                repeatCount++;
            }
        }

        if(repeatCount == 0){
            gameFrames << new GameFrame(this, key.game, key, controller);
        }
    }

    if(!gameFrames.isEmpty()){
        tabGameFrames.at(1)->append(gameFrames);
    }
    if(tabSetupCount < 2){
        addGamesTab("Claimed", 1);
    }
}

void LibraryWidget::addGamesTab(const QString& title, int tab)
{
    ui->tabWidget->addTab(tabScrollAreas.at(tab), title);
    QFont font("sans-serif", 12);
    font.setStyleStrategy(QFont::PreferAntialias);
    ui->tabWidget->setFont(font);

    tabSetupCount++;

    if(tabSetupCount == 2) {
        gameFrameWidth = tabGameFrames.at(0)->at(0)->width();
        maxGameFramesPerRow = (ui->tabWidget->width() - 80) / gameFrameWidth;

        adjustTabLayouts(true);
    }
}

void LibraryWidget::resizeEvent(QResizeEvent *event)
{
    event->accept();

    if(tabSetupCount == 2) {
        adjustTabLayouts();
    }
}

void LibraryWidget::adjustTabLayouts(bool forceAdjust)
{
    if(forceAdjust || ((ui->tabWidget->width() - 80) / gameFrameWidth != maxGameFramesPerRow)){
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
            maxGameFramesPerRow = (ui->tabWidget->width() - 80) / gameFrameWidth;

            tabRowLayouts.at(k)->append(new QVBoxLayout);
            tabColLayouts.at(k)->append(new QHBoxLayout);

            tabLayouts.at(k)->addLayout(tabRowLayouts.at(k)->at(0));
            tabRowLayouts.at(k)->at(0)->addLayout(tabColLayouts.at(k)->at(0));

            int i = 1;
            int j = 0;

            while(i < tabGameFrames.at(k)->size() + 1) {
                tabColLayouts.at(k)->at(j)->addWidget(tabGameFrames.at(k)->at(i - 1));

                if(i % maxGameFramesPerRow == 0) {
                    tabColLayouts.at(k)->append(new QHBoxLayout);

                    j++;

                    tabRowLayouts.at(k)->at(0)->addLayout(tabColLayouts.at(k)->at(j));
                }

                i++;
            }

            int o = tabGameFrames.at(k)->size() % maxGameFramesPerRow;

            if(o > 0){
                int p = maxGameFramesPerRow - (tabGameFrames.at(k)->size() % maxGameFramesPerRow);
                while(p > 0) {
                    tabColLayouts.at(k)->at(j)->addSpacerItem(new QSpacerItem(gameFrameWidth + 5, 0));

                    p--;
                }
            }

            tabWrappers.at(k)->setLayout(tabLayouts.at(k));
            tabScrollAreas.at(k)->setWidget(tabWrappers.at(k));
        }
    }
}

void LibraryWidget::onUpdate()
{
    int gameCount = 0;

    for(int i = 0; i < tabGameFrames.size(); i++){
        gameCount += tabGameFrames.at(i)->size();
    }

    controller->api->myOwnedKeys([this](QList<DownloadKey> keys) {
        onMyPurchasedKeys(keys);
    });

    controller->api->myClaimedKeys([this](QList<DownloadKey> keys) {
        onMyClaimedKeys(keys);
    });

    int newGameCount = 0;

    for(int i = 0; i < tabGameFrames.size(); i++){
        newGameCount += tabGameFrames.at(i)->size();
    }

    if(gameCount != newGameCount){
        adjustTabLayouts();

        int gameCountDifference = newGameCount - gameCount;
        QString notificationMessage = ((gameCountDifference > 1) ?
                                           (gameCountDifference + " new games available.") :
                                           ("1 new game available."));

        controller->showTrayIconNotification(TrayNotifications::LIBRARY_UPDATE, notificationMessage);
    }
}

LibraryWidget::~LibraryWidget()
{
    delete ui;
}
