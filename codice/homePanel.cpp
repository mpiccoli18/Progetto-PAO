#include "homePanel.h"
#include <QString>
#include <QVBoxLayout>
#include <QSplineSeries>>
#include <QtCharts>
#include <iostream>

namespace sensore{
    homePanel::homePanel(sensore::Sensore &s, QWidget* p):  QWidget(p), sensoreGenerale(s)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);

        pannello = new SensorPanel(sensoreGenerale);
        layout->addWidget(pannello);
        connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
    }

    void homePanel::Modify(){

    }

    void homePanel::Simulation(){
        double media = sensoreGenerale.StartSimulation();
        QSplineSeries *series = new QSplineSeries();
        std::vector<double> valori = sensoreGenerale.getValues();
        int iteratore = 1;
        for(auto i = valori.begin(); i != valori.end(); i++){
            series -> append(iteratore, *i);
            iteratore++;
            std::cout << *i << std::endl;
        }

        QChart *grafico = new QChart();
        grafico->addSeries(series);
        grafico->legend()->hide();
        grafico->setTitle("" + QString::fromStdString(sensoreGenerale.getType()) + " di: " + QString::fromStdString(sensoreGenerale.getName()));
        grafico->createDefaultAxes();
        grafico->axes(Qt::Vertical).first()->setRange(sensoreGenerale.getValueMin(), sensoreGenerale.getValueMax());

        QChartView *chartView = new QChartView(grafico);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->show();

    }
}
