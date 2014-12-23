#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

#include "appcontroller.h"
#include "appsettings.h"

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
    void onLoginTentative();
    void onLoginFailure(QString error);
    void onLogin();
    void onLoginByKeyFailure();

    void on_loginButton_clicked();
    void on_loginUsernameInput_returnPressed();
    void on_loginPasswordInput_returnPressed();
};

#endif // LOGINWIDGET_H
