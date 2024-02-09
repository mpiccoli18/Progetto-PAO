#include "mainwindow.h"
#include "homePanel.h"
#include<vector>

namespace sensore{
    MainWindow::MainWindow(std::vector<sensore::Sensore*> s){
        homePanel* home = new homePanel(*s[0], this);//primo sensore nel vettore
        setCentralWidget(home);
    }

    MainWindow::~MainWindow() {}
}
