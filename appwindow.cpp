#include "appwindow.h"
#include "ui_appwindow.h"
#include "widgets/loginwidget.h"
#include "widgets/librarywidget.h"

#include <QtDebug>
#include <QDesktopWidget>

//TODO: QDesktopWidget::​screenNumber might not be working properly. Returns 0 in all screens.

AppWindow::AppWindow(AppController* controller, QWidget* parent) :
    QMainWindow(parent),
    currentWidget(""),
    ui(new Ui::AppWindow),
    controller(controller),
    firstClicked(NULL)
{
    setWindowFlags( Qt::CustomizeWindowHint |  Qt::FramelessWindowHint );
    setWindowIcon(QIcon(":/images/images/itchio-icon-200.png"));

    ui->setupUi(this);

    move(QApplication::desktop()->screen(QApplication::desktop()->screenNumber(this))->rect().center() - rect().center());

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
}

void AppWindow::setupLogin()
{
    currentWidget = "Login";

    loginWidget = new LoginWidget(this, controller);
    widgetsLayout->addWidget(loginWidget);
    loginWidget->show();

    onWidgetChange(loginWidget);
    sizeGrip->hide();
}

void AppWindow::setupLibrary()
{
    currentWidget = "Library";
    libraryWidget = new LibraryWidget(this, controller);
    widgetsLayout->addWidget(libraryWidget);
    libraryWidget->show();
    sizeGrip->show();

    onWidgetChange(libraryWidget);
}

void AppWindow::onWidgetChange(QWidget* newWidget)
{
    setWindowTitle(currentWidget + " - itch.io");

    QSize oldSize = size();

    setMinimumSize(newWidget->minimumSize().width(), newWidget->minimumSize().height() + topBar->height());

    QSize newSize = size();

    if(oldSize.width() < newSize.width())
    {
        move(x() + (oldSize.width() - newSize.width())/2, y());
    }

    if(oldSize.height()< newSize.height())
    {
        move(x(), y() + (oldSize.height() - newSize.height())/2);
    }

    sizeGrip->raise();
}

void AppWindow::on_topBarCloseButton_clicked()
{
    close();
}
