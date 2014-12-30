#include <QDesktopWidget>

#include <QtDebug>

#include "appwindow.h"
#include "ui_appwindow.h"
#include "widgets/librarywidget.h"
#include "widgets/secondary/loginwidget.h"

AppWindow::AppWindow(AppController* controller, QWidget* parent) :
    QMainWindow(parent),
    currentWidget(""),
    desktop(QApplication::desktop()),
    ui(new Ui::AppWindow),
    controller(controller),
    firstClicked(NULL),
    isMaximized(false)
{
    setWindowFlags( Qt::CustomizeWindowHint |  Qt::FramelessWindowHint );
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    ui->setupUi(this);

    appWindowLayout = findChild<QGridLayout*>("appWindowLayout");
    widgetsLayout = findChild<QGridLayout*>("widgetsLayout");
    topBar = findChild<QWidget*>("topBar");

    setupSizeGrip();

    move(QApplication::desktop()->screen(QApplication::desktop()->screenNumber(0))->rect().center() - rect().center());
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::mousePressEvent(QMouseEvent *event)
{
    if(firstClicked == NULL) {
        firstClicked = childAt(event->x(), event->y());

        if(firstClicked == topBar) {
            dragClickX = event->x();
            dragClickY = event->y();
        }
    }

    event->accept();
}

void AppWindow::mouseReleaseEvent(QMouseEvent *event)
{
    firstClicked = NULL;

    event->accept();
}

void AppWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(firstClicked == topBar && !isMaximized) {
        move(event->globalX()-dragClickX, event->globalY()-dragClickY);
    }

    event->accept();
}

void AppWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(childAt(event->x(), event->y()) == topBar && currentWidget != "login") {
        if(!isMaximized) {
            maximize();
        } else {
            restore();
        }
    }

    event->accept();
}

void AppWindow::showWindow()
{
    setWindowFlags(windowFlags() ^ Qt::Tool);
    show();
    setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void AppWindow::hideWindow()
{
    setWindowFlags(windowFlags() ^ Qt::Tool);
    hide();
}

void AppWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    hideWindow();
}

void AppWindow::maximize()
{
    oldSize = size();
    oldPosition = pos();

    setGeometry(desktop->availableGeometry(desktop->screenNumber(this)));
    isMaximized = true;
}

void AppWindow::restore()
{
    setGeometry(oldPosition.x(), oldPosition.y(), oldSize.width(), oldSize.height());
    isMaximized = false;
}

void AppWindow::setupSizeGrip()
{
    sizeGrip = new QSizeGrip(this);
    appWindowLayout->addWidget(sizeGrip, 0, 0, 0, 0, Qt::AlignBottom | Qt::AlignRight);
}

void AppWindow::setupLibrary()
{
    currentWidget = "Library";
    libraryWidget = new LibraryWidget(this, controller);
    widgetsLayout->addWidget(libraryWidget);

    show();
    libraryWidget->show();
    sizeGrip->show();
    setWindowState(windowState() & Qt::WindowActive);

    onWidgetChange(libraryWidget);
}

void AppWindow::onWidgetChange(QWidget* newWidget)
{
    setWindowTitle(currentWidget + " - itch.io");

    QSize beforeSize = size();

    setMinimumSize(newWidget->minimumSize().width(), newWidget->minimumSize().height() + topBar->height());

    QSize afterSize = size();

    if(beforeSize.width() < afterSize.width()) {
        move(x() + (beforeSize.width() - afterSize.width())/2, y());
    }

    if(beforeSize.height()< afterSize.height()) {
        move(x(), y() + (beforeSize.height() - afterSize.height())/2);
    }

    oldSize = size();
    oldPosition = pos();

    sizeGrip->raise();
}

void AppWindow::on_topBarCloseButton_clicked()
{
    close();
}
