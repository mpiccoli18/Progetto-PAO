#include "homePanel.h"
#include "SensorInfoVisitor.h"
#include <QString>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QtCharts>
#include <QLineEdit>
#include<iostream>

namespace sensore{
homePanel::homePanel(std::vector<Sensore*> v,Sensore* s, QWidget* p):  QWidget(p), sensoreGenerale(s), chartView(nullptr), modifyView(nullptr)
    {
        // layout completo
        QVBoxLayout* layout = new QVBoxLayout(this);
        // menu
        QGridLayout* menu = new QGridLayout();
        layout->addLayout(menu);
        // layout barra e sensore
        layoutApp = new QHBoxLayout();
        layout->addLayout(layoutApp);

        QPushButton* save = new QPushButton("Salva");
        menu->addWidget(save, 0, 0, 1, 1);
        connect(save, &QPushButton::pressed, this, &homePanel::StartSave);
        connect(this, &homePanel::StartSave, this, &homePanel::Save);

        QPushButton* open = new QPushButton("Apri");
        menu->addWidget(open, 0, 2, 1, 1);
        connect(open, &QPushButton::pressed, this, &homePanel::StartOpen);
        connect(this, &homePanel::StartOpen, this, &homePanel::Open);

        QPushButton* close = new QPushButton("Chiudi");
        menu->addWidget(close, 0, 3, 1, 1);
        connect(close, &QPushButton::pressed, this, &homePanel::StartClose);
        connect(this, &homePanel::StartClose, this, &homePanel::close);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        menu->addItem(spacer, 0, 4, 1, 1);

        barraRicerca = new searchBarPanel(v);//barra
        layoutApp->addWidget(barraRicerca,1);
        barraRicerca->setFixedWidth(350);

        pannello = new SensorPanel();//sensore
        layoutApp->addWidget(pannello,2);

        layoutApp->setStretch(0, 1);
        layoutApp->setStretch(1, 2);

        connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
    }

    void homePanel::Save(){

    }

    void homePanel::Open(){

    }

    void homePanel::Close(){ // piu avanti

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

        QVBoxLayout* modLayout = new QVBoxLayout(modifyView);

        QLabel *labelname = new QLabel("Nome Sensore:");
        QLineEdit *lineName = new QLineEdit(this->pannello);

        QLabel *labeltype = new QLabel("Tipologia:");
        QLineEdit *lineType = new QLineEdit(this->pannello);

        QLabel *labeldescr = new QLabel("Descrizione:");
        QLineEdit *lineDescr = new QLineEdit(this->pannello);

        QLabel *labelmin = new QLabel("Valore Min:");
        QLineEdit *lineMin = new QLineEdit(this->pannello);

        QLabel *labelmax = new QLabel("Valore Max:");
        QLineEdit *lineMax = new QLineEdit(this->pannello);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit *lineVal = new QLineEdit(this->pannello);

        // Ottieni i nomi dei sensori utilizzando le funzioni getName()
        std::string name = sensoreGenerale->getName();
        std::string type = sensoreGenerale->getType();
        std::string descr = sensoreGenerale->getDescription();
        double min = sensoreGenerale->getValueMin();
        double max = sensoreGenerale->getValueMax();
        std::vector<double> v = sensoreGenerale->getValues();

        // Converti le std::string in QString
        QString qname = QString::fromStdString(name);
        QString qtype = QString::fromStdString(type);
        QString qdescr = QString::fromStdString(descr);
        QString qmin = QString::number(min);
        QString qmax = QString::number(max);
        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        // Imposta il testo nei campi di input
        lineName->setText(qname);
        lineType->setText(qtype);
        lineDescr->setText(qdescr);
        lineMin->setText(qmin);
        lineMax->setText(qmax);
        lineVal->setText(qval);

        modLayout->addWidget(lineName);
        modLayout->addWidget(lineType);
        modLayout->addWidget(lineDescr);
        modLayout->addWidget(lineMin);
        modLayout->addWidget(lineMax);
        modLayout->addWidget(lineVal);

        // Imposta le dimensioni dei campi di input
        int fieldWidth = this->pannello->width() /3; // Larghezza della metà del widget padre
        lineName->setFixedWidth(fieldWidth);
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);

        // Aggiungi i campi di input al layout
        modLayout->addWidget(labelname);
        modLayout->addWidget(lineName, 0, Qt::AlignLeft);

        modLayout->addWidget(labeltype);
        modLayout->addWidget(lineType, 0, Qt::AlignLeft);

        modLayout->addWidget(labeldescr);
        modLayout->addWidget(lineDescr, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmin);
        modLayout->addWidget(lineMin, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmax);
        modLayout->addWidget(lineMax, 0, Qt::AlignLeft);

        modLayout->addWidget(labelval);
        modLayout->addWidget(lineVal, 0, Qt::AlignLeft);



        SensorInfoVisitor visitor;
        sensoreGenerale->acceptModify(visitor);
        modLayout->addWidget(visitor.getWidget());

        // Aggiungi pulsante di conferma
        QPushButton *confirmButton = new QPushButton("Conferma", this->pannello);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        connect(confirmButton, &QPushButton::pressed, this, &homePanel::StartUpdate); // sistemare
        connect(this, &homePanel::StartUpdate, this, &homePanel::Update);

        QPushButton *exitButton = new QPushButton("Annulla", this->pannello);
        modLayout->addWidget(exitButton, 0, Qt::AlignLeft);
        connect(exitButton, &QPushButton::pressed, this, &homePanel::StartExit);
        connect(this, &homePanel::StartExit, this, &homePanel::Exit);

        // Aggiungi il widget con i campi di input e il pulsante al layout del pannello
        this->pannello->layout()->addWidget(modifyView);


        /*QString nome = nomeLine->text();
        QString tipo = tipoLine->text();
        QString descrizione = descrizioneLine->text();
        std::vector<double> valori;
        int valoreMin = valMinLine->text().toInt();
        int valoreMax = valMaxLine->text().toInt();

        int iterator = 0;
        for(auto i = valoriLine->text().begin(); i != valoriLine->text().end(); i++)
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
        qDebug() << "Nome cambiato: " <<this->sensoreGenerale.getName();*/
    }

    void homePanel::Update(){

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

        QSplineSeries *series = new QSplineSeries();
        std::vector<double> valori = sensoreGenerale->getValues();
        int iteratore = 1;
        for(auto i = valori.begin(); i != valori.end(); i++){
            series -> append(iteratore, *i);
            iteratore++;
        }

        QChart *grafico = new QChart();
        grafico->addSeries(series);
        grafico->legend()->hide();
        grafico->setTitle("" + QString::fromStdString(sensoreGenerale->getType()) + " di: " + QString::fromStdString(sensoreGenerale->getName()));

        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0, 12);
        axisX->setTickCount(13);
        grafico->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(sensoreGenerale->getValueMin(), sensoreGenerale->getValueMax());
        axisY->setTickCount(13);
        axisY->applyNiceNumbers();
        grafico->addAxis(axisY, Qt::AlignLeft);


        chartView = new QChartView(grafico);
        chartView->setRenderHint(QPainter::Antialiasing);
        this->pannello->layout()->addWidget(chartView);
    }

    void homePanel::Exit(){
        if(modifyView){
            this->pannello->layout()->removeWidget(modifyView);
            delete modifyView; // Libera la memoria
            modifyView = nullptr;
        }
    }

    void homePanel::Elimination() {
        // Rimuovi il sensore corrente
        delete sensoreGenerale;
    
        // Crea un nuovo sensore vuoto (o nullo)
        sensoreGenerale = nullptr; // oppure crea un nuovo sensore vuoto se necessario

        // Aggiorna il SensorPanel con il nuovo sensore
        pannello->updateSensor(sensoreGenerale);
    }

    void homePanel::View(Sensore* s){
        // Rimuovi il vecchio SensorPanel
        if(pannello)
        {
            this->layout()->removeWidget(pannello);
            if(chartView)
                chartView = nullptr;
            if(modifyView)
                modifyView = nullptr;
            delete pannello;
            // Crea e aggiungi il nuovo SensorPanel con il sensore selezionato
            pannello = new SensorPanel(s);
            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
            connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
            connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
        }
    }

}
