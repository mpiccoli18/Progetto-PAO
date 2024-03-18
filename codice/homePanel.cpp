#include "homePanel.h"
#include <QChartView>
#include <vector>

namespace sensore{
homePanel::homePanel(QWidget* p):  QWidget(p), grafico(nullptr), modifica(nullptr), creazione(nullptr), sceltaGrafico(nullptr)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QGridLayout* menu = new QGridLayout();

        layout->addLayout(menu);
        layoutApp = new QHBoxLayout();
        layout->addLayout(layoutApp);

        QPushButton* save = new QPushButton("Salva con nome");
        save->setObjectName("buttonSave");
        save->setStyleSheet("QPushButton#buttonSave {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                            "QPushButton#buttonSave:hover{background-color: lightgrey;}");
        save->setFixedWidth(125);
        menu->addWidget(save, 0, 0, 1, 1);
        connect(save, &QPushButton::pressed, this, &homePanel::StartSave);
        connect(this, &homePanel::StartSave, this, &homePanel::Save);

        saveStessoFile = new QPushButton("Salva");
        saveStessoFile->setObjectName("buttonSaveStesso");
        saveStessoFile->setStyleSheet("QPushButton#buttonSaveStesso {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                      "QPushButton#buttonSaveStesso:hover{background-color: lightgrey;}");
        saveStessoFile->setFixedWidth(125);
        menu->addWidget(saveStessoFile, 0, 2, 1, 1);
        saveStessoFile->setEnabled(false);
        connect(saveStessoFile, &QPushButton::pressed, this, &homePanel::StartSaveStessoFile);
        connect(this, &homePanel::StartSaveStessoFile, this, &homePanel::SaveStessoFile);

        QPushButton* open = new QPushButton("Apri");
        open->setObjectName("buttonOpen");
        open->setStyleSheet("QPushButton#buttonOpen {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                            "QPushButton#buttonOpen:hover{background-color: lightgrey;}");
        open->setFixedWidth(125);
        menu->addWidget(open, 0, 3, 1, 1);
        connect(open, &QPushButton::pressed, this, &homePanel::StartOpen);
        connect(this, &homePanel::StartOpen, this, &homePanel::Open);

        QPushButton* create = new QPushButton("Crea");
        create->setObjectName("buttonCreate");
        create->setStyleSheet("QPushButton#buttonCreate {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                              "QPushButton#buttonCreate:hover{background-color: lightgrey;}");
        create->setFixedWidth(125);
        menu->addWidget(create, 0, 4, 1, 1);
        connect(create, &QPushButton::pressed, this, &homePanel::StartCreate);
        connect(this, &homePanel::StartCreate, this, &homePanel::Create);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        menu->addItem(spacer, 0, 5, 1, 1);

        mod = new modello();
        barraRicerca = new searchBarPanel(mod);// barra di ricerca
        layoutApp->addWidget(barraRicerca,1);

        pannello = new SensorPanel();// sensore
        layoutApp->addWidget(pannello,2);

        layoutApp->setStretch(0, 1);
        layoutApp->setStretch(1, 2);

        connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
        connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
        connect(this, &homePanel::StartSensorSelected, this, &homePanel::SensorSelected);
    }

    void homePanel::Open(){
        if(creazione){
            layoutApp->layout()->removeWidget(creazione);
            delete creazione;
            creazione = nullptr;

            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(mod);
            pannello = new SensorPanel();
            layoutApp->addWidget(barraRicerca, 1);
            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
            connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
            connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
            connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
        }
        if(modificato == true && !(nomeFile.isEmpty()))
        {
            QWidget *noModifiche = new QWidget();
            QVBoxLayout *modificheLayout = new QVBoxLayout();
            noModifiche->setLayout(modificheLayout);
            QLabel* mod = new QLabel("Attenzione: hai delle modifiche non salvate!");
            mod->setStyleSheet("font: bold 16px");
            modificheLayout->addWidget(mod);
            QPushButton* salva = new QPushButton("Salva");
            QPushButton* annulla = new QPushButton("Annulla");
            modificheLayout->addWidget(salva);
            modificheLayout->addWidget(annulla);
            connect(salva, &QPushButton::pressed, this, [=]{
                SaveStessoFile();
                noModifiche->close();
                modificato = false;
            });
            connect(annulla, &QPushButton::pressed, this, [=] {
                noModifiche->close();
            });
            noModifiche->show();
        }
        else if(modificato == true)
        {
            QWidget *noModifiche = new QWidget();
            QVBoxLayout *modificheLayout = new QVBoxLayout();
            noModifiche->setLayout(modificheLayout);
            QLabel* mod = new QLabel("Attenzione: hai delle modifiche non salvate!");
            mod->setStyleSheet("font: bold 16px");
            modificheLayout->addWidget(mod);
            QPushButton* salva = new QPushButton("Salva con nome");
            QPushButton* annulla = new QPushButton("Annulla");
            modificheLayout->addWidget(salva);
            modificheLayout->addWidget(annulla);
            connect(salva, &QPushButton::pressed, this, [=]{
                Save();
                noModifiche->close();
                modificato = false;
            });
            connect(annulla, &QPushButton::pressed, this, [=] {
                noModifiche->close();
            });
            noModifiche->show();
        }
        else
        {

            QString filePath = QFileDialog::getOpenFileName(this, tr("Apri file JSON"), "", tr("File JSON (*.json)"));
            nomeFile = filePath;
            if(!(nomeFile.isEmpty()))
            {
                mod->pulisciInsieme();
            }
            int warning = mod->apriSens(filePath);
            if(warning == 1)
            {
                QMessageBox::warning(this, tr("Errore"), tr("Il file selezionato è vuoto!"));
                return;
            }
            if(warning == 2)
            {
                QMessageBox::warning(this, tr("Errore"), tr("Impossibile aprire il file"));
                return;
            }
            if(warning == 3)
            {
                QMessageBox::warning(this, tr("Errore"), tr("Il file non contiene un oggetto JSON valido."));
                return;
            }
            QMessageBox::information(this, tr("Successo"), tr("Sensori caricati con successo!"));

        }
        if(barraRicerca)
        {
            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(mod);
            pannello = new SensorPanel();
            layoutApp->addWidget(barraRicerca, 1);
            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
            connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
            connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
            connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
        }
    }

    void homePanel::Save(){

        QString filePath = QFileDialog::getSaveFileName(this, tr("Salva file JSON"), "", tr("File JSON (*.json)"));

        int warning = mod->salvaSens(filePath);

        if(warning == 1)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Il file selezionato è vuoto!"));
            return;
        }
        if(warning == 2)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile creare il file!"));
            return;
        }
        if(!(filePath.isEmpty()))
        {
            modificato = false;
        }
        QMessageBox::information(this, tr("Successo"), tr("Dati salvati nel file JSON: ") + filePath);
    }

    void homePanel::SaveStessoFile(){

        int warning = mod->salvaSens(nomeFile);

        if(warning == 1)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Il file selezionato è vuoto!"));
            return;
        }
        if(warning == 2)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile creare il file!"));
            return;
        }
        QMessageBox::information(this, tr("Successo"), tr("Dati salvati nel file JSON: ") + nomeFile);
        saveStessoFile->setEnabled(false);
        modificato = false;
    }

    void homePanel::Create() {
        if(barraRicerca){
            layoutApp->layout()->removeWidget(barraRicerca);
            delete pannello;
            pannello = nullptr;
            delete barraRicerca;
            barraRicerca = nullptr;
        }
        if(creazione)
        {
            layoutApp->layout()->removeWidget(creazione);
            delete creazione;
            creazione = nullptr;
        }
        barraRicerca = new searchBarPanel(mod);
        connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);

        creazione = new QWidget();
        QVBoxLayout* createLayout = new QVBoxLayout();
        creazione->setLayout(createLayout);
        QLabel* labeltitle = new QLabel("Creazione di un Sensore");
        labeltitle->setAlignment(Qt::AlignCenter);
        labeltitle->setStyleSheet("font: bold 14px;");
        createLayout->addWidget(labeltitle);

        QLabel* labeltype = new QLabel("Tipologia:");
        QLineEdit* lineType = new QLineEdit(creazione);

        QLabel* labeldescr = new QLabel("Descrizione:");
        QLineEdit* lineDescr = new QLineEdit(creazione);

        QLabel* labelmin = new QLabel("Valore minimo:");
        QLineEdit* lineMin = new QLineEdit(creazione);

        QLabel* labelmax = new QLabel("Valore massimo:");
        QLineEdit* lineMax = new QLineEdit(creazione);

        QLabel* labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit* lineVal = new QLineEdit(creazione);

        createLayout->addWidget(labeltype, 0, Qt::AlignTop);
        createLayout->addWidget(lineType, 0, Qt::AlignTop);
        createLayout->addWidget(labeldescr, 0, Qt::AlignTop);
        createLayout->addWidget(lineDescr, 0, Qt::AlignTop);
        createLayout->addWidget(labelmin, 0, Qt::AlignTop);
        createLayout->addWidget(lineMin, 0, Qt::AlignTop);
        createLayout->addWidget(labelmax, 0, Qt::AlignTop);
        createLayout->addWidget(lineMax, 0, Qt::AlignTop);
        createLayout->addWidget(labelval, 0, Qt::AlignTop);
        createLayout->addWidget(lineVal, 0, Qt::AlignTop);


        QLabel* labelbox = new QLabel("Scegli il tipo del Sensore:");
        createLayout->addWidget(labelbox);

        QComboBox* sensorTypeComboBox = new QComboBox();
        sensorTypeComboBox->addItem("Sensore Consumo");
        sensorTypeComboBox->addItem("Sensore Motore");
        sensorTypeComboBox->addItem("Sensore Batteria");
        sensorTypeComboBox->addItem("Sensore Gas");
        sensorTypeComboBox->addItem("Sensore Pneumatico");

        createLayout->addWidget(sensorTypeComboBox);
        creazione->setFixedHeight(500);

        connect(sensorTypeComboBox, QOverload<int>::of(&QComboBox::activated), [=](int index) {
                QString selectedOption = sensorTypeComboBox->itemText(index);
                emit StartSensorSelected(lineType, lineDescr, lineMin, lineMax, lineVal, selectedOption, createLayout);
        });

        layoutApp->addWidget(barraRicerca, 1);
        layoutApp->addWidget(creazione, 2);
        layoutApp->setStretch(0, 1);
        layoutApp->setStretch(1, 2);
    }

    void homePanel::SensorSelected(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor, QVBoxLayout* createLayout)
    {
        while (createLayout->count() > 13) {
            QLayoutItem* item = createLayout->takeAt(13);
            delete item->widget();
            delete item;
        }

        if (selectedSensor == "Sensore Batteria") {
            QLabel* labelmat = new QLabel("Materiali:");
            QLineEdit* lineMat = new QLineEdit(creazione);
            createLayout->addWidget(labelmat);
            createLayout->addWidget(lineMat);
            QPushButton* confirmButton = new QPushButton("Conferma");
            createLayout->addWidget(confirmButton);
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineMat]() {
                mod->creaSensBatteria(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineMat);
                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod);
                    pannello = new SensorPanel();
                    layoutApp->addWidget(barraRicerca, 1);
                    layoutApp->addWidget(pannello, 2);
                    layoutApp->setStretch(0, 1);
                    layoutApp->setStretch(1, 2);
                    connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
                    connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
                    connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
                    connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
                }
                if(!nomeFile.isEmpty())
                {
                    saveStessoFile->setEnabled(true);
                }
                modificato = true;
                QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
            });
        }
        if (selectedSensor == "Sensore Consumo") {
            QLabel* labelott = new QLabel("Numero di Ottano:");
            QLineEdit* lineOtt = new QLineEdit(creazione);
            createLayout->addWidget(labelott);
            createLayout->addWidget(lineOtt);

            QPushButton* confirmButton = new QPushButton("Conferma");
            createLayout->addWidget(confirmButton);
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineOtt]() {
                mod->creaSensConsumo(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineOtt);
                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod);
                    pannello = new SensorPanel();
                    layoutApp->addWidget(barraRicerca, 1);
                    layoutApp->addWidget(pannello, 2);
                    layoutApp->setStretch(0, 1);
                    layoutApp->setStretch(1, 2);
                    connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
                    connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
                    connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
                    connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
                }
                if(!nomeFile.isEmpty())
                {
                    saveStessoFile->setEnabled(true);
                }
                modificato = true;
                QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
            });
        }
        if (selectedSensor == "Sensore Motore") {
            QLabel* labelcav = new QLabel("Numero di Cavalli:");
            QLineEdit* lineCav = new QLineEdit(creazione);
            createLayout->addWidget(labelcav);
            createLayout->addWidget(lineCav);

            QPushButton* confirmButton = new QPushButton("Conferma");
            createLayout->addWidget(confirmButton);
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineCav]() {
                mod->creaSensMotore(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineCav);
                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod);
                    pannello = new SensorPanel();
                    layoutApp->addWidget(barraRicerca, 1);
                    layoutApp->addWidget(pannello, 2);
                    layoutApp->setStretch(0, 1);
                    layoutApp->setStretch(1, 2);
                    connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
                    connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
                    connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
                    connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
                }
                if(!nomeFile.isEmpty())
                {
                    saveStessoFile->setEnabled(true);
                }
                modificato = true;
                QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
            });
        }
        if (selectedSensor == "Sensore Gas") {
            QLabel* labelfootp = new QLabel("Impronta:");
            QLineEdit* lineFootp = new QLineEdit(creazione);
            createLayout->addWidget(labelfootp);
            createLayout->addWidget(lineFootp);

            QPushButton* confirmButton = new QPushButton("Conferma");
            createLayout->addWidget(confirmButton);
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineFootp]() {
                mod->creaSensConsumo(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineFootp);
                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod);
                    pannello = new SensorPanel();
                    layoutApp->addWidget(barraRicerca, 1);
                    layoutApp->addWidget(pannello, 2);
                    layoutApp->setStretch(0, 1);
                    layoutApp->setStretch(1, 2);
                    connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
                    connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
                    connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
                    connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
                }
                if(!nomeFile.isEmpty())
                {
                    saveStessoFile->setEnabled(true);
                }
                modificato = true;
                QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
            });
        }
        if (selectedSensor == "Sensore Pneumatico") {
            QLabel* labelbr = new QLabel("Marca:");
            QLineEdit* lineBr = new QLineEdit(creazione);
            createLayout->addWidget(labelbr);
            createLayout->addWidget(lineBr);
            QLabel* labelage = new QLabel("Tempo di vita:");
            QLineEdit* lineAge = new QLineEdit(creazione);
            createLayout->addWidget(labelage);
            createLayout->addWidget(lineAge);

            QPushButton* confirmButton = new QPushButton("Conferma");
            createLayout->addWidget(confirmButton);
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineBr, lineAge]() {
                mod->creaSensPneumatico(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineAge, lineBr);
                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod);
                    pannello = new SensorPanel();
                    layoutApp->addWidget(barraRicerca, 1);
                    layoutApp->addWidget(pannello, 2);
                    layoutApp->setStretch(0, 1);
                    layoutApp->setStretch(1, 2);
                    connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
                    connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
                    connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
                    connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);

                }
                if(!nomeFile.isEmpty())
                {
                    saveStessoFile->setEnabled(true);
                }
                modificato = true;
                QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
            });
        }
    }

    void homePanel::Modify(Sensore *s){
        if(modifica)
        {
            modifica->close();
        }
        SensorInfoVisitor visitor;
        visitor.setModello(mod);
        s->acceptMod(visitor);
        modifica = visitor.getWidget();

        QPushButton* confirmButton = visitor.getButton();
        QPushButton *exitButton = new QPushButton("Annulla", modifica);

        modifica->layout()->addWidget(exitButton);
        modifica->layout()->addWidget(confirmButton);
        modifica->show();

        connect(confirmButton, &QPushButton::pressed, this, [=](){
            if (sceltaGrafico) {
                this->pannello->layout()->removeWidget(sceltaGrafico);
                delete sceltaGrafico;
                sceltaGrafico = nullptr;
            }
            if (grafico) {
                this->pannello->layout()->removeWidget(grafico);
                delete grafico;
                grafico = nullptr;
            }
            if(modifica){
                delete barraRicerca;
                barraRicerca = new searchBarPanel(mod);
                delete pannello;
                pannello = new SensorPanel(s);
                layoutApp->addWidget(barraRicerca, 1);
                layoutApp->addWidget(pannello, 2);
                layoutApp->setStretch(0, 1);
                layoutApp->setStretch(1, 2);
                connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
                connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
                connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
                connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
            }
            QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato aggiornato!"));
            saveStessoFile->setEnabled(true);
            modificato = true;
            modifica->close();
        });

        connect(exitButton, &QPushButton::pressed, this, [=](){
            modifica->close();
        });
    }

    void homePanel::Simulation(){
        if (sceltaGrafico) {
            this->pannello->layout()->removeWidget(sceltaGrafico);
            delete sceltaGrafico;
            sceltaGrafico = nullptr;
        }
        if (grafico) {
            this->pannello->layout()->removeWidget(grafico);
            delete grafico;
            grafico = nullptr;
        }
        std::vector<double> valori = sensoreGenerale->getValori();

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->setTitle("" + QString::fromStdString(sensoreGenerale->getTipo()) + " di: " + QString::fromStdString(sensoreGenerale->getNome()));

        // Asse X
        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0, valori.size()+1);
        axisX->setTickCount(valori.size()+2);
        axisX->setLabelFormat("%d");
        chart->addAxis(axisX, Qt::AlignBottom);

        // Asse Y
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(sensoreGenerale->getMin(), sensoreGenerale->getMax());
        axisY->setTickCount(10);
        axisY->applyNiceNumbers();
        chart->addAxis(axisY, Qt::AlignLeft);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        sceltaGrafico = new QComboBox();
        sceltaGrafico->setFixedWidth(250);
        // Aggiungi un elemento vuoto non selezionabile
        sceltaGrafico->addItem("Scegli una tipologia di grafico");
        // Aggiungi gli altri tipi di grafico
        sceltaGrafico->addItem("Spline");
        sceltaGrafico->addItem("Punti");
        sceltaGrafico->addItem("Linee");
        sceltaGrafico->addItem("Barra");
        connect(sceltaGrafico, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
            switch(index) {
                case 1: // Spline
                    chart->removeAllSeries();
                    {
                        QSplineSeries* splineGrafico = new QSplineSeries();
                        for (int i = 0; i < valori.size(); ++i)
                            splineGrafico->append(i + 1, valori[i]);
                        chart->addSeries(splineGrafico);
                        splineGrafico->attachAxis(axisX);
                        splineGrafico->attachAxis(axisY);
                    }
                    break;
                case 2: // Punti
                    chart->removeAllSeries();
                    {
                        QScatterSeries* scatterGrafico = new QScatterSeries();
                        for (int i = 0; i < valori.size(); ++i)
                            scatterGrafico->append(i + 1, valori[i]);
                        chart->addSeries(scatterGrafico);
                        scatterGrafico->attachAxis(axisX);
                        scatterGrafico->attachAxis(axisY);
                    }
                    break;
                case 3: // Linee
                    chart->removeAllSeries();
                    {
                        QLineSeries *lineGrafico = new QLineSeries();
                        for (int i = 0; i < valori.size(); ++i)
                            lineGrafico->append(i + 1, valori[i]);
                        chart->addSeries(lineGrafico);
                        lineGrafico->attachAxis(axisX);
                        lineGrafico->attachAxis(axisY);
                    }
                    break;
                case 4: // Barra
                    chart->removeAllSeries();
                    {
                        QBarSeries *barraGrafico = new QBarSeries();
                        QBarSet* set = new QBarSet("Valori");
                        for (int i = 0; i < valori.size(); i++) {
                            if(i == 0) *set << 0;
                            *set << valori[i];
                            barraGrafico->append(set);
                        }
                        //barraGrafico->append(set);
                        chart->addSeries(barraGrafico);
                        barraGrafico->attachAxis(axisX);
                        barraGrafico->attachAxis(axisY);
                    }
                    break;
                default:
                    break;
            }
        });

        grafico = new QChartView(chart);
        grafico->setStyleSheet("border: 1px solid black; border-radius: 2px; background-color:lightgrey;");
        grafico->setRenderHint(QPainter::Antialiasing);
        grafico->setMaximumSize(1200, 700);
        this->pannello->layout()->addWidget(sceltaGrafico);
        this->pannello->layout()->addWidget(grafico);
    }

    void homePanel::keyPressEvent(QKeyEvent* event)
    {

        switch (event->key())
        {
            case Qt::Key_Plus:
                zoomIn();
                break;
            case Qt::Key_Minus:
                zoomOut();
                break;
            case Qt::Key_A:
                moveChart(-1);
                break;
            case Qt::Key_D:
                moveChart(1);
                break;
            case Qt::Key_W:
                moveVChart(1);
                break;
            case Qt::Key_S:
                moveVChart(-1);
                break;
            case Qt::Key_Escape:
                resetChart();
                break;
        }
    }

    void homePanel::zoomIn()
    {
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        grafico->chart()->zoomIn();
        asseX->setTickCount(asseX->tickCount() / 2 + zoomGrafico);
        //qDebug() << asseX->tickCount();
        zoomGrafico++;
    }

    void homePanel::zoomOut()
    {
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        grafico->chart()->zoomOut();
        asseX->setTickCount(asseX->tickCount() * 2 + zoomGrafico);
        zoomGrafico--;
    }

    void homePanel::moveChart(int direzione)
    {
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        if (!asseX)
            return;
        double min = asseX->min();
        double max = asseX->max();
        int val = 0;
        asseX->setLabelFormat("%d");
        if(zoomGrafico > 0)
        {
            if(min == 0)
                val = (max + 1 + zoomGrafico) / 14 * direzione;
            else if(min < 0)
                val = (max - min + 1 + zoomGrafico) / 14 * direzione;
            else
                val = (max + min + 1 + zoomGrafico) / 14 * direzione;
        }
        else
        {
            if(min == 0)
                val = (max + 1) / 14 * direzione;
            else if(min < 0)
                val = (max - min + 1) / 14 * direzione;
            else
                val = (max + min + 1) / 14 * direzione;
        }
        asseX->setRange(min + val, max + val);
        /*qDebug() << min;
        qDebug() << max;
        qDebug() << val;
        qDebug() << zoomGrafico;*/
    }

    void homePanel::moveVChart(int direzione)
    {
        QValueAxis* asseY = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Vertical).at(0));
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        if (!asseY)
            return;

        int val = 0;
        asseX->setLabelFormat("%d");
        if(grafico->chart()->isZoomed())
        {
            val = 5 * direzione;
        }
        else
        { 
            val = 10 * direzione;
        }
        asseY->setRange(asseY->min() + val, asseY->max() + val);
    }

    void homePanel::resetChart()
    {
        grafico->chart()->zoomReset();
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        asseX->setLabelFormat("%d");
        asseX->setTickCount(14);
        zoomGrafico = 1;
    }

    void homePanel::Elimination(Sensore* s) {
        if(modifica)
            modifica = nullptr;
        if(grafico)
            grafico = nullptr;
        if(sceltaGrafico)
            sceltaGrafico = nullptr;
        mod->eliminaSens(s);
        sensoreGenerale = nullptr;
        s = nullptr;
        if(pannello)
        {
            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(mod);
            pannello = new SensorPanel();
            layoutApp->addWidget(barraRicerca, 1);
            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
            connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
            connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
            connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
        }
        if(!(nomeFile.isEmpty()))
        {
            saveStessoFile->setEnabled(true);
        }
        modificato = true;
    }


    void homePanel::View(Sensore* s){ 
        if(pannello)
        {
            this->layout()->removeWidget(pannello);
            if(grafico)
                grafico = nullptr;
            if(sceltaGrafico)
                sceltaGrafico = nullptr;
            if(modifica)
                modifica = nullptr;

            delete pannello;
            pannello = new SensorPanel(s);
            sensoreGenerale = s;

            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
            connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
            connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
        }
        if(creazione)
        {
            delete creazione;

            pannello = new SensorPanel(s);
            sensoreGenerale = s;

            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::StartSimulation, this, &homePanel::Simulation);
            connect(pannello, &SensorPanel::StartModify, this, &homePanel::Modify);
            connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
        }
    }
}
