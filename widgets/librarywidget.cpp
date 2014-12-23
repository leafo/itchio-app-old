#include "librarywidget.h"
#include "ui_librarywidget.h"

#include <gameswindow.h>

#include <QtDebug>

LibraryWidget::LibraryWidget(QWidget *parent, AppController *controller) :
    QWidget(parent),
    ui(new Ui::LibraryWidget),
    controller(controller)
{
    ui->setupUi(this);
}

LibraryWidget::~LibraryWidget()
{
    delete ui;
}
