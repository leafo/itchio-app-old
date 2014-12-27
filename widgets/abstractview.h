#ifndef APPWIDGET_H
#define APPWIDGET_H

#include <QWidget>
#include <QScopedPointer>

namespace itchio {

template<class UserInterface, class Controller, class Model>
class AbstractView : public QWidget
{
    Q_STATIC_ASSERT_X(std::is_default_constructible<UserInterface>::value, "UserInterface requires a default constructor.");

protected:
    AbstractView(Controller& controller, Model& model, QWidget* const parent) :
        QWidget(parent),
        ui_(new UserInterface),
        controller_(controller),
        model_(model)
    {
        Q_ASSERT(!ui_.isNull());
        ui_->setupUi(this);
    }

    const QScopedPointer<UserInterface> ui_;

    // TODO Make model_ a const reference. In true MVC fashion, the model should never be modified by the view.
    Controller& controller_;
    Model& model_;
};

} // namespace itchio

#endif // APPWIDGET_H
