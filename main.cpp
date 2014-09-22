#include "gameswindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GamesWindow w;
    w.show();

    return a.exec();
}
