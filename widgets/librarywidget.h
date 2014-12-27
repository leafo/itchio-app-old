#ifndef LIBRARYWIDGET_H
#define LIBRARYWIDGET_H

#include "abstractview.h"
#include "ui_librarywidget.h"
#include "objects/downloadkey.h"

namespace itchio {

class GameRow;

//TODO Remove these when a proper Library and LibraryController has been implemented.
class Api;
class AppController;
using LibraryController = AppController; //TODO Remove this when a proper LibraryController has been implemented.
using Library = Api; //TODO Remove this when a proper Library has been implemented.

class LibraryWidget : public AbstractView<Ui::LibraryWidget, LibraryController, Library>
{
    Q_OBJECT

public:
    LibraryWidget(LibraryController& controller, QWidget* const parent);

public slots:
    void onMyOwnedKeys(const QList<DownloadKey>& downloadKeys);

private:
    void addGamesTab(const QString& title, const QList<GameRow*>& gameRows);
};

} // namespace itchio

#endif // LIBRARYWIDGET_H
