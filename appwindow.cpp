#include "appwindow.h"
#include "ui_appwindow.h"
#include "widgets/loginwidget.h"
#include "widgets/librarywidget.h"

#include <QtDebug>

AppWindow::AppWindow(AppController* controller, QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::AppWindow),
    controller(controller),
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
    loginWidget = new LoginWidget(this, controller);
    widgetsLayout->addWidget(loginWidget);
    loginWidget->show();

    onWidgetChange(loginWidget);
}

void AppWindow::setupLibrary()
{
    libraryWidget = new LibraryWidget(this, controller);
    widgetsLayout->addWidget(libraryWidget);
    libraryWidget->show();

    onWidgetChange(libraryWidget);
}

void AppWindow::onWidgetChange(QWidget* newWidget)
{
    newWidgetSizeDiference = newWidget->minimumSize() - size();

    if(width() < newWidget->minimumWidth()) {
        setGeometry(x() - newWidgetSizeDiference.width()/2, y(), width(), newWidget->minimumHeight());
    }

    if(height() < newWidget->minimumHeight()) {
        setGeometry(x(), y() - newWidgetSizeDiference.height()/2, width(), newWidget->minimumHeight());
    }

    sizeGrip->raise();
}

void AppWindow::on_topBarCloseButton_clicked()
{
    close();
}
