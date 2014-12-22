#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

#include "appcontroller.h"

namespace Ui
{
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(AppController* controller, QWidget* parent = 0);
    ~LoginWidget();

private:
    Ui::LoginWidget* ui;
    AppController* controller;

    void setStatus(QString status, bool disable);

private slots:
    void on_loginButton_clicked();

    void onLoginFailure(QString);
    void onLogin();

};

#endif // LOGINWIDGET_H
