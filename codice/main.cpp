#include "mainwindow.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel hello("Hello!");
    MainWindow w;
    hello.show();
    return a.exec();
}
