#include "logindialog.h"
#include "ui_logindialog.h"

#include <QtDebug>

LoginDialog::LoginDialog(AppController *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog),
    controller(controller)
{
    ui->setupUi(this);
    connect(controller->api, SIGNAL(onLoginFailure(QString)), this, SLOT(onLoginFailure(QString)));
    connect(controller->api, SIGNAL(onLogin()), this, SLOT(onLogin()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLogin()
{
    controller->showGames();
}

void LoginDialog::onLoginFailure(QString error)
{
    setStatus(error, false);
}

void LoginDialog::on_loginButton_clicked()
{
    QString username = ui->usernameInput->text();
    QString password =  ui->passwordInput->text();
    if (username == "" or password == "") {
        setStatus("Please enter username and password", false);
        return;
    }

    setStatus("Logging in...", true);
    controller->api->login(username, password);
}

void LoginDialog::setStatus(QString status, bool disable)
{
    ui->statusLabel->setText(status);
    ui->usernameInput->setDisabled(disable);
    ui->passwordInput->setDisabled(disable);
    ui->loginButton->setDisabled(disable);
}
