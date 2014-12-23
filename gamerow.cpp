#include "gamerow.h"

#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QUrlQuery>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#include <QPixmap>

int GameRow::COVER_HEIGHT = 80;

GameRow::GameRow(QWidget *parent, Game game) :
    QWidget(parent),
    game(game)
{
    QHBoxLayout* rowLayout = new QHBoxLayout;
    downloadButton = new QPushButton("Download");

    imageHolder = new QLabel();
    double ratio = double(Game::COVER_WIDTH) / Game::COVER_HEIGHT;

    imageHolder->setFixedWidth(int(COVER_HEIGHT * ratio));
    imageHolder->setFixedHeight(COVER_HEIGHT);
    imageHolder->setScaledContents(true);
    imageHolder->setObjectName("imageHolder");

    downloadProgress = new QProgressBar();
    downloadProgress->setMinimum(0);
    downloadProgress->setMaximum(100);

    rowLayout->addWidget(imageHolder);


    QWidget* infoWidget = new QWidget();
    QVBoxLayout* infoWidgetLayout = new QVBoxLayout();
    infoWidgetLayout->addWidget(new QLabel(game.title));
    infoWidgetLayout->addWidget(new QLabel(game.user.nameForDisplay()));
    infoWidget->setLayout(infoWidgetLayout);

    rowLayout->addWidget(infoWidget, 1);
    rowLayout->addWidget(downloadButton, 0);

    setLayout(rowLayout);

    connect(downloadButton, SIGNAL(clicked()), SLOT(onClickDownload()));

    refreshThumbnail();
}

GameRow::~GameRow()
{
}

void GameRow::onClickDownload()
{
    qDebug() << "clicked download" << game.title;
    layout()->removeWidget(downloadButton);
    downloadButton->hide();

    qobject_cast<QHBoxLayout*>(layout())->addWidget(downloadProgress, 0);
    downloadProgress->setMaximum(0);
}

void GameRow::onDownloadThumbnail()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error downloading thumbnail" << reply->errorString();
        return;
    }

    QByteArray imageData = reply->readAll();
    QPixmap pixmap;
    if (pixmap.loadFromData(imageData)) {
        imageHolder->setPixmap(pixmap);
    }
}

void GameRow::refreshThumbnail()
{
    if (game.coverImageUrl == "") {
        return;
    }

    QNetworkAccessManager* networkManager = new QNetworkAccessManager(this);

    qDebug() << "Fetching cover" << game.coverImageUrl;
    QNetworkReply* reply = networkManager->get(QNetworkRequest(QUrl(game.coverImageUrl)));
    connect(reply, SIGNAL(finished()), this, SLOT(onDownloadThumbnail()));
}
