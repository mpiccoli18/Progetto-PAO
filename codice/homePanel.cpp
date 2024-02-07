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
        sensoreGenerale.StartSimulation();
        QSplineSeries *series = new QSplineSeries();
        std::vector<double> valori = sensoreGenerale.getValues();
        int iteratore = 1;
        for(auto i = valori.begin(); i != valori.end(); i++){
            series -> append(iteratore, *i);
            iteratore++;
        }

        QChart *grafico = new QChart();
        grafico->addSeries(series);
        grafico->legend()->hide();
        grafico->setTitle("" + QString::fromStdString(sensoreGenerale.getType()) + " di: " + QString::fromStdString(sensoreGenerale.getName()));

        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0, 12);
        axisX->setTickCount(13);
        grafico->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(sensoreGenerale.getValueMin(), sensoreGenerale.getValueMax());
        axisY->setTickCount(13);
        axisY->applyNiceNumbers();
        grafico->addAxis(axisY, Qt::AlignLeft);


        QChartView *chartView = new QChartView(grafico);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setFixedHeight(600);
        chartView->setFixedWidth(600);
        this->pannello->layout()->addWidget(chartView);
    }
}
