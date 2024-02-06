#include "mainwindow.h"
#include "sensoreBatteria.h"
#include <QApplication>
#include <vector>

int main(int argc, char *argv[])
{
    std::vector<double> v = {5, 10, 14, 20, 52, 62, 70, 80, 75, 82, 85, 93};
    QApplication app(argc, argv);
    sensore::SensoreBatteria s("Sens-2045", "Consumo", "boh", v, 0, 100, "litio");
    sensore::MainWindow window(s);
    window.resize(1024, 512);
    window.show();
    return app.exec();
}
