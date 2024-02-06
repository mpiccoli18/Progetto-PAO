#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sensore.h"

namespace sensore{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
            MainWindow(sensore::Sensore&);
            ~MainWindow();
    };
}

#endif // MAINWINDOW_H
