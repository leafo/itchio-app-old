#include "logindialog.h"
#include "ui_logindialog.h"
#include "itchioapi.h"

#include <QtDebug>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    api = new ItchioApi(this);
    connect(api, SIGNAL(onLoginFailure(QString)), this, SLOT(onLoginFailure(QString)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::onLogin() {
}

void LoginDialog::onLoginFailure(QString error) {
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

    setStatus("Loggin in...", true);
    api->login(username, password);
}

void LoginDialog::setStatus(QString status, bool disable) {
    ui->statusLabel->setText(status);
    ui->usernameInput->setDisabled(disable);
    ui->passwordInput->setDisabled(disable);
    ui->loginButton->setDisabled(disable);
}
