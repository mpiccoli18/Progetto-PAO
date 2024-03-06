#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "homePanel.h"

namespace sensore{

    class MainWindow : public QMainWindow
    {
        Q_OBJECT
        private:
            homePanel* home;
        public:
        MainWindow();
        ~MainWindow();
    };
}

#endif // MAINWINDOW_H
