#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QCloseEvent>

#include "appcontroller.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(AppController* controller, QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_loginButton_clicked();
    void onLoginFailure(QString);
    void onLogin();

private:
    void closeEvent(QCloseEvent *event);

    Ui::LoginDialog* ui;
    AppController* controller;

    void setStatus(QString status, bool disable);
};

#endif // LOGINDIALOG_H
