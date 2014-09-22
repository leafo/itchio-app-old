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
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    qDebug() << "do something" << api;
}
