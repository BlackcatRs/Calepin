#include <QApplication>

#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow	 mainWindow("Liste de personnes");

    mainWindow.show();

    return app.exec();
}
