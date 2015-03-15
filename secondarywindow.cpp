#include "secondarywindow.h"
#include "ui_secondarywindow.h"

#include <QMouseEvent>

#include <QtDebug>

SecondaryWindow::SecondaryWindow(QWidget* const widget, AppController* const controller,
                                 bool startsVisible, bool showTopBar, QWidget* const parent)
    : QDialog(parent)
    , name("")
    , firstClicked(NULL)
    , ui(new Ui::SecondaryWindow)
    , controller(controller)
    , widget(widget)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    ui->setupUi(this);

    setWindowTitle(widget->windowTitle() + " - itch.io");

    name = widget->objectName();

    resize(widget->minimumSize());
    setMinimumSize(widget->minimumSize().width(), widget->minimumSize().height() + ui->topBar->height());

    ui->widgetsLayout->addWidget(widget);

    widget->show();

    widget->setParent(this);

    setVisible(startsVisible);
    ui->topBar->setVisible(showTopBar);
}

SecondaryWindow::~SecondaryWindow()
{
    delete ui;
}

void SecondaryWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();

    closeWindow();

    if(widget->windowTitle() == "Login" && controller->api->userName == ""){
        controller->quit();
    }
}

void SecondaryWindow::closeWindow()
{
    hide();
}

void SecondaryWindow::mousePressEvent(QMouseEvent* event)
{
    if (firstClicked == NULL) {
        firstClicked = childAt(event->x(), event->y());

        if (firstClicked == ui->topBar) {
            dragClickX = event->x();
            dragClickY = event->y();
        }
    }
}

void SecondaryWindow::mouseReleaseEvent(QMouseEvent* event)
{
    firstClicked = NULL;

    event->accept();
}

void SecondaryWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (firstClicked == ui->topBar) {
        move(event->globalX() - dragClickX, event->globalY() - dragClickY);
    }
}

void SecondaryWindow::on_topBarCloseButton_clicked()
{
    close();
}
