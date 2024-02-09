#include "mainwindow.h"
#include "sensoreBatteria.h"
#include <QApplication>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<double> v = {44, 95, 50, 14, 20, 52, 62, 70, 80, 75, 82, 85, 93};
    QApplication app(argc, argv);
    sensore::SensoreBatteria s("Sens-2045", "Consumo", "boh", v, 0, 100, "litio");
    sensore::MainWindow window(s);
    window.resize(1600, 1000);
    window.show();
    return app.exec();
}
