#include "gamerow.h"

#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

GameRow::GameRow(QWidget *parent, Game game) :
    QWidget(parent),
    game(game)
{
    QHBoxLayout* rowLayout = new QHBoxLayout;

    QPushButton* downloadButton =  new QPushButton("Download");

    rowLayout->addWidget(new QLabel(game.title), 1);
    rowLayout->addWidget(downloadButton, 0);

    setLayout(rowLayout);

    connect(downloadButton, SIGNAL(clicked()), SLOT(onClickDownload()));
}

GameRow::~GameRow()
{
}

void GameRow::onClickDownload()
{
    qDebug() << "clicked download" << game.title;
}
