#include "homePanel.h"
#include <QString>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QtCharts>
#include <iostream>

namespace sensore{
    homePanel::homePanel(sensore::Sensore &s, QWidget* p):  QWidget(p), sensoreGenerale(s)
    {
        QVBoxLayout* menulayout = new QVBoxLayout(this);

        QGridLayout* menu = new QGridLayout();
        menulayout->addLayout(menu);

        QHBoxLayout* layout = new QHBoxLayout();
        menulayout->addLayout(layout);

        QPushButton* save = new QPushButton("Salva");
        menu->addWidget(save, 0, 0, 1, 1);
        connect(save, &QPushButton::pressed, this, &homePanel::StartModify);
        QPushButton* open = new QPushButton("Apri");
        menu->addWidget(open, 0, 2, 1, 1);
        connect(open, &QPushButton::pressed, this, &SensorPanel::StartModify);
        QPushButton* close = new QPushButton("Chiudi");
        menu->addWidget(close, 0, 3, 1, 1);
        connect(close, &QPushButton::pressed, this, &SensorPanel::StartModify);
        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        menu->addItem(spacer, 0, 4, 1, 1);

        barraRicerca = new SensorPanel(sensoreGenerale);//barra
        layout->addWidget(0,1);

        pannello = new SensorPanel(sensoreGenerale);
        layout->addWidget(pannello,2);

        layout->setStretch(0, 1);
        layout->setStretch(1, 2);
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
        this->pannello->layout()->addWidget(chartView);
    }
}
