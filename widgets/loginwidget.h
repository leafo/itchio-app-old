#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include "abstractview.h"
#include "ui_loginwidget.h"

namespace itchio {

class Api;

//TODO Remove these when a proper LoginController has been implemented.
class AppController;
using LoginController = AppController;

class LoginWidget : public AbstractView<Ui::LoginWidget, LoginController, Api>
{
    Q_OBJECT

public:
    LoginWidget(LoginController& controller, QWidget* const parent);

private:
    void setStatus(const QString& status, bool disable);

private slots:
    void onLoginTentative();
    void onLoginFailure(const QString& error);
    void onLogin();
};

} // namespace itchio

#endif // LOGINWIDGET_H
