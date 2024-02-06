#include "mainwindow.h"
#include "homePanel.h"


namespace sensore{
    MainWindow::MainWindow(sensore::Sensore& s){
        homePanel* home = new homePanel(s, this);
        setCentralWidget(home);
    }

    MainWindow::~MainWindow() {}
}
