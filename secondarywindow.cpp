#include "secondarywindow.h"
#include "ui_secondarywindow.h"
#include "appwindow.h"
#include "widgets/secondary/settingswidget.h"

#include <QMouseEvent>

#include <QtDebug>

using itchio::SecondaryWindow;

SecondaryWindow::SecondaryWindow(AppWindow& appWindow) :
    name(""),
    firstClicked(NULL),
    ui(new Ui::SecondaryWindow),
    controller(appWindow.controller()),
    settingsWidget(new SettingsWidget(controller, this))
{
    setWindowFlags(Qt::CustomizeWindowHint |  Qt::FramelessWindowHint );
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    ui->setupUi(this);

    setWindowTitle(settingsWidget->windowTitle() + " - itch.io");

    name = settingsWidget->objectName();

    topBar = findChild<QWidget*>("topBar");

    resize(settingsWidget->minimumSize());
    setMinimumSize(settingsWidget->minimumSize().width(), settingsWidget->minimumSize().height() + topBar->height());

    widgetsLayout = findChild<QGridLayout*>("widgetsLayout");
    widgetsLayout->addWidget(settingsWidget);
    settingsWidget->show();
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
