#include "mainwindow.h"
#include "homePanel.h"
#include<vector>

namespace sensore{
    MainWindow::MainWindow(std::vector<sensore::Sensore*> s){
        homePanel* home = new homePanel(s,s[0], this);//puntatore primo sensore nel vettore
        setCentralWidget(home);
    }

    MainWindow::~MainWindow() {}
}
