#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<vector>
#include "sensore.h"

namespace sensore{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

        public:
        MainWindow(std::vector<sensore::Sensore*> s);
        ~MainWindow();
    };
}

#endif // MAINWINDOW_H
