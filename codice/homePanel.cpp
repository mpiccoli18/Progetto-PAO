#include "homePanel.h"
#include "SensorInfoVisitor.h"
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
            this->pannello->layout()->removeWidget(modifyView);
            delete modifyView; // Libera la memoria
            modifyView = nullptr;
        }

        modifyView = new QWidget();

        // Crea un layout per contenere i campi di input e il pulsante
        QVBoxLayout* modLayout = new QVBoxLayout(modifyView);

        // Aggiungi label1 e input1
        QLabel *label1 = new QLabel("Nome Sensore:");
        QLineEdit *lineEdit1 = new QLineEdit(this->pannello);


        // Aggiungi label2 e input2
        QLabel *label2 = new QLabel("Tipologia:");
        QLineEdit *lineEdit2 = new QLineEdit(this->pannello);

        // Ottieni i nomi dei sensori utilizzando le funzioni getName()
        std::string name = sensoreGenerale.getName();
        std::string type = sensoreGenerale.getType();

        // Converti le std::string in QString
        QString qname = QString::fromStdString(name);
        QString qtype = QString::fromStdString(type);

        // Imposta il testo nei campi di input
        lineEdit1->setText(qname);
        lineEdit2->setText(qtype);

        modLayout->addWidget(lineEdit1);

        modLayout->addWidget(lineEdit2);

        // Imposta le dimensioni dei campi di input
        int fieldWidth = this->pannello->width() / 2; // Larghezza della metà del widget padre
        lineEdit1->setFixedWidth(fieldWidth);
        lineEdit2->setFixedWidth(fieldWidth);

        // Aggiungi i campi di input al layout
        modLayout->addWidget(label1);
        modLayout->addWidget(lineEdit1, 0, Qt::AlignLeft);

        modLayout->addWidget(label2);
        modLayout->addWidget(lineEdit2, 0, Qt::AlignLeft);

        // Aggiungi pulsante di conferma
        QPushButton *confirmButton = new QPushButton("Conferma", this->pannello);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);

        QPushButton *exitButton = new QPushButton("Annulla", this->pannello);
        modLayout->addWidget(exitButton, 0, Qt::AlignLeft);

        SensorInfoVisitor visitor;
        sensoreGenerale.accept(visitor);
        modLayout->addWidget(visitor.getWidget());

        // Aggiungi il widget con i campi di input e il pulsante al layout del pannello
        this->pannello->layout()->addWidget(modifyView);



        /*
        QString nome = nomeLine->text();
        QString tipo = tipoLine->text();
        QString descrizione = descrizioneLine->text();
        std::vector<double> valori;
        int valoreMin = valMinLine->text().toInt();
        int valoreMax = valMaxLine->text().toInt();

        int iterator = 0;
        /for(auto i = valoriLine->text().begin(); i != valoriLine->text().end(); i++)
        {
            if(i == )
            {
                continue;
            }
            else
            {
                valori = i;
            }
        }/

                // Esempio di utilizzo delle variabili salvate
                qDebug() << "Dato 1:" << nome;
        qDebug() << "Dato 2:" << tipo;
        qDebug() << "Dato 3:" << descrizione;
        qDebug() << "Dato 4:" << valori;
        qDebug() << "Dato 5:" << valoreMin;
        qDebug() << "Dato 6:" << valoreMax;

        this->sensoreGenerale.setName(nome.toStdString());
        this->pannello->refresh(sensoreGenerale);
        qDebug() << "Nome cambiato: " <<this->sensoreGenerale.getName(); */
    }

    void homePanel::Simulation(){
        if (chartView) {
            this->pannello->layout()->removeWidget(chartView);
            delete chartView; // Libera la memoria
        }
        if(modifyView){
            this->pannello->layout()->removeWidget(modifyView);
            delete modifyView; // Libera la memoria
            modifyView = nullptr;
        }

        /*sensoreGenerale.StartSimulation();*/
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
