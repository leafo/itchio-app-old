#include "gamerow.h"
#include "ui_gamerow.h"

GameRow::GameRow(QWidget *parent, Game game) :
    QWidget(parent),
    ui(new Ui::GameRow),
    game(game)
{
    ui->setupUi(this);
}

GameRow::~GameRow()
{
    delete ui;
}
