#include "mainwindow.h"
#include "homePanel.h"

namespace sensore{
    MainWindow::MainWindow(){
        home = new homePanel(this);
        setCentralWidget(home);
    }

    MainWindow::~MainWindow() {
        delete home;
    }
}
