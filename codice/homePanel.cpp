#include "homePanel.h"
#include <QString>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QtCharts>
#include <QLineEdit>
#include <iostream>

namespace sensore{
homePanel::homePanel(sensore::Sensore &s, QWidget* p):  QWidget(p), sensoreGenerale(s)
    {
        // layout completo
        QVBoxLayout* layout = new QVBoxLayout(this);
        // menu
        QGridLayout* menu = new QGridLayout();
        layout->addLayout(menu);
        // layout barra e sensore
        QHBoxLayout* layoutApp = new QHBoxLayout();
        layout->addLayout(layoutApp);


        QPushButton* save = new QPushButton("Salva");
        menu->addWidget(save, 0, 0, 1, 1);
        connect(save, &QPushButton::pressed, this, &homePanel::StartSave);
        connect(this, &homePanel::StartSave, this, &homePanel::save);

        QPushButton* open = new QPushButton("Apri");
        menu->addWidget(open, 0, 2, 1, 1);
        connect(open, &QPushButton::pressed, this, &homePanel::StartOpen);
        connect(this, &homePanel::StartOpen, this, &homePanel::open);

        QPushButton* close = new QPushButton("Chiudi");
        menu->addWidget(close, 0, 3, 1, 1);
        connect(close, &QPushButton::pressed, this, &homePanel::StartClose);
        connect(this, &homePanel::StartClose, this, &homePanel::close);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        menu->addItem(spacer, 0, 4, 1, 1);

        barraRicerca = new SensorPanel(sensoreGenerale);//barra
        layoutApp->addWidget(barraRicerca,1);

        pannello = new SensorPanel(sensoreGenerale);//sensore
        layoutApp->addWidget(pannello,2);

        connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
        connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);

        layoutApp->setStretch(0, 1);
        layoutApp->setStretch(1, 2);
    }

    void homePanel::save(){

    }

    void homePanel::open(){

    }

    void homePanel::close(){ // piu avanti

    }

    void homePanel::Modify(){
        if (chartView) {
            this->pannello->layout()->removeWidget(chartView);
            delete chartView; // Libera la memoria
            chartView = nullptr;
        }
        if(modifyView){
            this->pannello->layout()->removeItem(modifyView);
            delete modifyView; // Libera la memoria
            modifyView = nullptr;
        }

        QVBoxLayout *modifyView = new QVBoxLayout(); // da aggiungere a pannello


        // Aggiungi campi di input
        QLineEdit *lineEdit1 = new QLineEdit(this->pannello);
        QLineEdit *lineEdit2 = new QLineEdit(this->pannello);

        // Imposta le dimensioni dei campi di input
        int fieldWidth = this->pannello->width() / 2; // Larghezza della metà del widget padre
        lineEdit1->setFixedWidth(fieldWidth);
        lineEdit2->setFixedWidth(fieldWidth);

        // Aggiungi i campi di input alla griglia
        modifyView->addWidget(lineEdit1, Qt::AlignLeft);
        modifyView->addWidget(lineEdit2, Qt::AlignLeft);

        // Aggiungi pulsante di conferma
        QPushButton *confirmButton = new QPushButton("Conferma", this->pannello);
        modifyView->addWidget(confirmButton);

        // Collega il click del pulsante alla funzione di salvataggio
        QObject::connect(confirmButton, &QPushButton::clicked, this->pannello, [=]() {
            // Salva i dati inseriti nelle variabili locali
            QString data1 = lineEdit1->text();
            QString data2 = lineEdit2->text();

            // Esempio di utilizzo delle variabili salvate
            qDebug() << "Dato 1:" << data1;
            qDebug() << "Dato 2:" << data2;
        });
    }

    void homePanel::Simulation(){
        if (chartView) {
            this->pannello->layout()->removeWidget(chartView);
            delete chartView; // Libera la memoria
        }

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


        chartView = new QChartView(grafico);
        chartView->setRenderHint(QPainter::Antialiasing);
        this->pannello->layout()->addWidget(chartView);
    }
}
