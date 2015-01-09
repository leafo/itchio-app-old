#include <QFile>

#include <QtDebug>

#include "appwindow.h"
#include "ui_appwindow.h"
#include "widgets/librarywidget.h"
#include "widgets/secondary/loginwidget.h"

// TODO: Research better ways to handle CSS change during runtime.

AppWindow::AppWindow(AppController* controller, QWidget* parent)
    : QMainWindow(parent)
    , currentWidget("")
    , isMaximized(false)
    , desktop(QApplication::desktop())
    , ui(new Ui::AppWindow)
    , controller(controller)
    , firstClicked(NULL)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    ui->setupUi(this);

    appWindowLayout = findChild<QGridLayout*>("appWindowLayout");
    widgetsLayout = findChild<QGridLayout*>("widgetsLayout");
    topBar = findChild<QWidget*>("topBar");

    topBarWidgetButtons = findChild<QWidget*>("widgetButtonsWidget")->findChildren<QPushButton*>();

    setupSizeGrip();

    connect(desktop, SIGNAL(workAreaResized(int)), this, SLOT(onDesktopResize()));
    connect(desktop, SIGNAL(screenCountChanged (int)), this, SLOT(onScreenCountChange ()));
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::mousePressEvent(QMouseEvent* event)
{
    if (firstClicked == NULL) {
        firstClicked = childAt(event->x(), event->y());

        if (firstClicked == topBar) {
            dragClickX = event->x();
            dragClickY = event->y();
        }
    }

    event->accept();
}

void AppWindow::mouseReleaseEvent(QMouseEvent* event)
{
    firstClicked = NULL;

    event->accept();
}

void AppWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (firstClicked == topBar && !isMaximized) {
        move(event->globalX() - dragClickX, event->globalY() - dragClickY);
    }

    event->accept();
}

void AppWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (childAt(event->x(), event->y()) == topBar) {
        if (!isMaximized) {
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

void AppWindow::closeEvent(QCloseEvent* event)
{
    event->ignore();

    hideWindow();
}

void AppWindow::maximize()
{
    sizeGrip->hide();

    oldSize = size();
    oldPosition = pos();

    setGeometry(desktop->availableGeometry(desktop->screenNumber(this)));
    isMaximized = true;
}

void AppWindow::restore()
{
    setGeometry(oldPosition.x(), oldPosition.y(), oldSize.width(), oldSize.height());
    isMaximized = false;

    sizeGrip->show();
}

void AppWindow::setupSizeGrip()
{
    sizeGrip = new QSizeGrip(this);
    appWindowLayout->addWidget(sizeGrip, 0, 0, 0, 0, Qt::AlignBottom | Qt::AlignRight);
}

void AppWindow::setupLibrary()
{
    libraryWidget = new LibraryWidget(this, controller);
    widgetsLayout->addWidget(libraryWidget);
    widgets.append(libraryWidget);
    libraryWidget->hide();

    onWidgetChange(libraryWidget);

    if(!controller->settings->windowGeometry().isEmpty()) {
        restoreGeometry(controller->settings->windowGeometry());
    } else {
        move(desktop->availableGeometry(0).center() - rect().center());
    }

    if(controller->settings->startMaximized()) {
        maximize();
    }

    oldPosition = controller->settings->windowOldPosition();

    if(oldSize.width() > desktop->availableGeometry(this).width()) {
        oldSize.setWidth(desktop->availableGeometry(this).width());
    }

    if(oldSize.height() > desktop->availableGeometry(this).height()) {
        oldSize.setHeight(desktop->availableGeometry(this).height());
    }
}

void AppWindow::onScreenCountChange()
{
    restoreGeometry(saveGeometry());
    if(isMaximized) {
        oldPosition = desktop->availableGeometry(desktop->screenNumber(this)).center() - rect().center();

        setGeometry(desktop->availableGeometry(desktop->screenNumber(this)));
    }
}

void AppWindow::onDesktopResize()
{
    restoreGeometry(saveGeometry());

    if(oldSize.width() > desktop->availableGeometry(this).width()) {
        oldSize.setWidth(desktop->availableGeometry(this).width());
    }

    if(oldSize.height() > desktop->availableGeometry(this).height()) {
        oldSize.setHeight(desktop->availableGeometry(this).height());
    }

    if(isMaximized) {
        setGeometry(desktop->availableGeometry(desktop->screenNumber(this)));
    }

    oldPosition = desktop->availableGeometry(desktop->screenNumber(this)).center() - rect().center();
}

void AppWindow::onWidgetChange(QWidget* newWidget)
{
    currentWidget = newWidget->windowTitle();
    setWindowTitle(currentWidget + " - itch.io");

    for (int i = 0; i != topBarWidgetButtons.count(); i++) {
        if (topBarWidgetButtons[i]->text() == currentWidget) {
            topBarWidgetButtons[i]->setStyleSheet("AppWindow #widgetButtonsWidget QPushButton { color: #fa6666; } AppWindow #widgetButtonsWidget QPushButton:pressed { color: #e44949; }");
        } else {
            topBarWidgetButtons[i]->setStyleSheet("AppWindow #widgetButtonsWidget QPushButton { color: #fff; } AppWindow #widgetButtonsWidget QPushButton:focus:!pressed, AppWindow #topBar QPushButton:hover:!pressed { color: #fa6666; } AppWindow #widgetButtonsWidget QPushButton:pressed { color: #e44949; }");
        }
    }

    QSize beforeSize = size();

    setMinimumSize(newWidget->minimumSize().width() + 10,
                   newWidget->minimumSize().height() + topBar->height() + 10);

    QSize afterSize = size();

    if (beforeSize.width() < afterSize.width()) {
        move(x() + (beforeSize.width() - afterSize.width()) / 2, y());
    }

    if (beforeSize.height() < afterSize.height()) {
        move(x(), y() + (beforeSize.height() - afterSize.height()) / 2);
    }

    oldSize = size();
    oldPosition = pos();

    for (int i = 0; i != widgets.count(); i++) {
        widgets[i]->hide();
        widgets[i]->lower();
    }

    show();
    newWidget->show();
    sizeGrip->show();
    sizeGrip->raise();
    setWindowState(windowState() & Qt::WindowActive);
}

void AppWindow::on_topBarCloseButton_clicked()
{
    close();
}

void AppWindow::on_libraryButton_clicked()
{
    if (currentWidget != libraryWidget->windowTitle()) {
        onWidgetChange(libraryWidget);
    }
}
