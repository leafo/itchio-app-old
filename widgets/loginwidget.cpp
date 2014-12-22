#include "loginwidget.h"
#include "ui_loginwidget.h"

#include <QtDebug>

LoginWidget::LoginWidget(AppController *controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    controller(controller)
{
    setWindowFlags( Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint );

    ui->setupUi(this);
    connect(controller->api, SIGNAL(onLoginFailure(QString)), this, SLOT(onLoginFailure(QString)));
    connect(controller->api, SIGNAL(onLogin()), this, SLOT(onLogin()));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::setStatus(QString status, bool disable)
{
    ui->loginStatusLabel->setText(status);
    ui->loginUsernameInput->setDisabled(disable);
    ui->loginPasswordInput->setDisabled(disable);
    ui->loginButton->setDisabled(disable);
}

void LoginWidget::on_loginButton_clicked()
{
    QString username = ui->loginUsernameInput->text();
    QString password =  ui->loginPasswordInput->text();

    if (username == "" || password == "") {
        setStatus("Please enter username and password", false);
        return;
    }

    setStatus("Logging in...", true);
    controller->api->login(username, password);
}

void LoginWidget::onLoginFailure(QString error)
{
    setStatus(error, false);
}

void LoginWidget::onLogin()
{
    controller->onLogin();
}
