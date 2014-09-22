#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "itchioapi.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void on_loginButton_clicked();
    void onLoginFailure(QString);
    void onLogin();

private:
    Ui::LoginDialog* ui;
    ItchioApi* api;

    void setStatus(QString status, bool disable);
};

#endif // LOGINDIALOG_H
