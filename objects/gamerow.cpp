#include "gamerow.h"
#include "ui_gamerow.h"

GameRow::GameRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameRow)
{
    ui->setupUi(this);
}

GameRow::~GameRow()
{
    delete ui;
}
