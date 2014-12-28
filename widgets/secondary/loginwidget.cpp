#include <QtDebug>

#include "loginwidget.h"
#include "ui_loginwidget.h"

LoginWidget::LoginWidget(QWidget *parent, AppController *controller) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    controller(controller)
{
    ui->setupUi(this);

    connect(controller->api, SIGNAL(onLoginFailure(QString)), this, SLOT(onLoginFailure(QString)));
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::setStatus(const QString& status, bool disable)
{
    ui->loginStatusLabel->setText(status);
    ui->loginUsernameInput->setDisabled(disable);
    ui->loginPasswordInput->setDisabled(disable);
    ui->loginButton->setDisabled(disable);
}

void LoginWidget::onLoginTentative()
{
    QString username = ui->loginUsernameInput->text();
    QString password =  ui->loginPasswordInput->text();

    if (username == "" || password == "") {
        setStatus("Please enter username and password", false);
        return;
    }

    setStatus("Logging in...", true);
    controller->api->loginWithPassword(username, password);
}

void LoginWidget::onLoginFailure(QString error)
{
    setStatus(error, false);
}

void LoginWidget::on_loginButton_clicked()
{
    onLoginTentative();
}

void LoginWidget::on_loginUsernameInput_returnPressed()
{
    onLoginTentative();
}

void LoginWidget::on_loginPasswordInput_returnPressed()
{
    onLoginTentative();
}
