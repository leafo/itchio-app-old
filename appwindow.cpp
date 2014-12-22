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
    appWindowLayout = findChild<QGridLayout*>("appWindowLayout");

    appWindowLayout->addWidget(new QSizeGrip(this), 0, 0, 0, 0, Qt::AlignBottom | Qt::AlignRight);


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
            dragClickX = event->x();
            dragClickY = event->y();
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
       move(event->globalX()-dragClickX, event->globalY()-dragClickY);
    }
}

void AppWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(childAt(event->x(), event->y()) == topBar){
        if(!isMaximized()) maximize();
        else restore();
    }
}

void AppWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    close();
}

void AppWindow::on_topBarCloseButton_clicked()
{
    close();
}

void AppWindow::close()
{
    controller->hide();
}

void AppWindow::maximize()
{
    oldSize = size();
    oldPosition = pos();

    showMaximized();
}

void AppWindow::restore()
{
    showNormal();
    setGeometry(oldPosition.x(), oldPosition.y(), oldSize.width(), oldSize.height());
}
