#include "appwindow.h"
#include "ui_appwindow.h"

#include <QtDebug>

AppWindow::AppWindow(AppController* controller, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::AppWindow),
    controller(controller)
{
    setWindowFlags( Qt::CustomizeWindowHint |  Qt::FramelessWindowHint );

    ui->setupUi(this);

    topBar = findChild<QWidget*>("topBar");
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::mousePressEvent(QMouseEvent *event)
{
    if(firstClicked == NULL){
        firstClicked = childAt(event->x(), event->y());

        if(firstClicked == topBar){
            leftClickX = event->x();
            leftClickY = event->y();
        }
    }
}

void AppWindow::mouseReleaseEvent(QMouseEvent *event)
{
    firstClicked = NULL;

    event->accept();
}

void AppWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(firstClicked == topBar && !isMaximized()){
       move(event->globalX()-leftClickX, event->globalY()-leftClickY);
    }
}

void AppWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(childAt(event->x(), event->y()) == topBar){
        if(!isMaximized())
        {
            oldSize = size();
            oldPosition = pos();
            showMaximized();
        }
        else
        {
            showNormal();
            resize(oldSize);
            setGeometry(oldPosition.x(), oldPosition.y(), oldSize.width(), oldSize.height());
        }
    }
}

void AppWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();
    controller->hide();
}

void AppWindow::on_topBarCloseButton_clicked()
{
    controller->hide();
}
