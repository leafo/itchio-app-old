#include "appwindow.h"
#include "ui_appwindow.h"
#include "widgets/loginwidget.h"
#include "widgets/librarywidget.h"

#include <QtDebug>

AppWindow::AppWindow(AppController* controller, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::AppWindow),
    controller(controller)
{
    setWindowFlags( Qt::CustomizeWindowHint |  Qt::FramelessWindowHint );

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
    if(childAt(event->x(), event->y()) == topBar) {
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

void AppWindow::setupSizeGrip()
{
    sizeGrip = new QSizeGrip(this);
    appWindowLayout->addWidget(sizeGrip, 0, 0, 0, 0, Qt::AlignBottom | Qt::AlignRight);
    sizeGrip->show();
}

void AppWindow::setupLogin()
{
    loginWidget = new LoginWidget(controller, this);
    widgetsLayout->addWidget(loginWidget);
    loginWidget->show();
    sizeGrip->raise();
}

void AppWindow::setupLibrary()
{
    libraryWidget = new LibraryWidget(controller, this);
    widgetsLayout->addWidget(libraryWidget);
    libraryWidget->show();

    loginToLibrarySizeDiference = size() - minimumSize();

    if(width() < libraryWidget->minimumWidth()) {
        setGeometry(x() - loginToLibrarySizeDiference.width(), y(), width(), libraryWidget->minimumHeight());
    }

    if(height() < libraryWidget->minimumHeight()) {
        setGeometry(x(), y() - loginToLibrarySizeDiference.height(), width(), libraryWidget->minimumHeight());
    }

    sizeGrip->raise();
}

void AppWindow::on_topBarCloseButton_clicked()
{
    close();
}
