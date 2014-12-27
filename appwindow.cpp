#include "appwindow.h"
#include "ui_appwindow.h"
#include "widgets/loginwidget.h"
#include "widgets/librarywidget.h"
#include "appcontroller.h"

#include <QtDebug>
#include <QDesktopWidget>

using itchio::AppWindow;

//TODO: QDesktopWidget::​screenNumber might not be working properly. Returns 0 in all screens.

AppWindow::AppWindow(AppController& controller) :
    currentWidget(""),
    ui(new Ui::AppWindow),
    controller_(controller),
    firstClicked(NULL)
{
    setWindowFlags( Qt::CustomizeWindowHint |  Qt::FramelessWindowHint );
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    ui->setupUi(this);

    appWindowLayout = findChild<QGridLayout*>("appWindowLayout");
    widgetsLayout = findChild<QGridLayout*>("widgetsLayout");
    topBar = findChild<QWidget*>("topBar");

    setupSizeGrip();
    setupLogin();
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
}

void AppWindow::mouseReleaseEvent(QMouseEvent *event)
{
    firstClicked = NULL;

    event->accept();
}

void AppWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(firstClicked == topBar && !isMaximized()) {
        move(event->globalX()-dragClickX, event->globalY()-dragClickY);
    }
}

void AppWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(childAt(event->x(), event->y()) == topBar && currentWidget != "login") {
        if(!isMaximized()) {
            maximize();
        } else {
            restore();
        }
    }
}

void AppWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    close();
}

void AppWindow::close()
{
    controller_.hide();
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

void AppWindow::setupSizeGrip()
{
    sizeGrip = new QSizeGrip(this);
    appWindowLayout->addWidget(sizeGrip, 0, 0, 0, 0, Qt::AlignBottom | Qt::AlignRight);
}

void AppWindow::setupLogin()
{
    currentWidget = "Login";

    loginWidget = new LoginWidget(controller_, this);
    widgetsLayout->addWidget(loginWidget);
    loginWidget->show();

    onWidgetChange(loginWidget);
    sizeGrip->hide();

    move(QApplication::desktop()->screen(QApplication::desktop()->screenNumber(this))->rect().center() - rect().center());
}

void AppWindow::setupLibrary()
{
    currentWidget = "Library";
    libraryWidget = new LibraryWidget(controller_, this);
    widgetsLayout->addWidget(libraryWidget);
    libraryWidget->show();
    sizeGrip->show();

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

    sizeGrip->raise();
}

void AppWindow::on_topBarCloseButton_clicked()
{
    close();
}
