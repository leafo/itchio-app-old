#include "librarywidget.h"
#include "ui_librarywidget.h"

#include <QtDebug>

LibraryWidget::LibraryWidget(AppController *controller, QWidget *parent) :
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
