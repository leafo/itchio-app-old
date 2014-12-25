#include "secondarywindow.h"
#include "ui_secondarywindow.h"

#include <QMouseEvent>

#include <QtDebug>

SecondaryWindow::SecondaryWindow(QWidget* const widget, AppController* const controller, QWidget* const parent) :
    QDialog(parent),
    name(""),
    firstClicked(NULL),
    ui(new Ui::SecondaryWindow),
    controller(controller),
    widget(widget)
{
    setWindowFlags(Qt::CustomizeWindowHint |  Qt::FramelessWindowHint );
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    ui->setupUi(this);

    setWindowTitle(widget->windowTitle() + " - itch.io");

    name = widget->objectName();

    topBar = findChild<QWidget*>("topBar");

    resize(widget->minimumSize());
    setMinimumSize(widget->minimumSize().width(), widget->minimumSize().height() + topBar->height());

    widgetsLayout = findChild<QGridLayout*>("widgetsLayout");
    widgetsLayout->addWidget(widget);
    widget->show();
}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}

void SecondaryWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    closeWindow();
}

void SecondaryWindow::closeWindow()
{
    deleteLater();
    close();
}

void SecondaryWindow::mousePressEvent(QMouseEvent *event)
{
    if(firstClicked == NULL) {
        firstClicked = childAt(event->x(), event->y());

        if(firstClicked == topBar) {
            dragClickX = event->x();
            dragClickY = event->y();
        }
    }
}

void SecondaryWindow::mouseReleaseEvent(QMouseEvent *event)
{
    firstClicked = NULL;

    event->accept();
}

void SecondaryWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(firstClicked == topBar) {
        move(event->globalX()-dragClickX, event->globalY()-dragClickY);
    }
}

void SecondaryWindow::on_topBarCloseButton_clicked()
{
    close();
}
