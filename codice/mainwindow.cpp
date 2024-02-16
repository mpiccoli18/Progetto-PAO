#include "mainwindow.h"
#include "homePanel.h"

namespace sensore{
    MainWindow::MainWindow(){
        homePanel* home = new homePanel(this);
        setCentralWidget(home);
    }

    MainWindow::~MainWindow() {}
}
