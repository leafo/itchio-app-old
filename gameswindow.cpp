#include "gameswindow.h"
#include "ui_gameswindow.h"

GamesWindow::GamesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GamesWindow)
{
    ui->setupUi(this);
}

GamesWindow::~GamesWindow()
{
    delete ui;
}
