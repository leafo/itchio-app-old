#include "gameswindow.h"
#include "ui_gameswindow.h"

GamesWindow::GamesWindow(AppController *controller, QWidget *parent) :
    QMainWindow(parent),
    controller(controller),
    ui(new Ui::GamesWindow)
{
    ui->setupUi(this);
}

GamesWindow::~GamesWindow()
{
    delete ui;
}
