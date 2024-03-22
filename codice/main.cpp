#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    sensore::MainWindow window ;
    window.resize(1600, 1000);

    window.show();
    return app.exec();
}
