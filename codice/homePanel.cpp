#include "SensorInfoVisitor.h"
#include "modello.h"
#include "homePanel.h"
#include <QString>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QtCharts>
#include <QLineEdit>
#include <iostream>
#include <vector>

namespace sensore{
    homePanel::homePanel(QWidget* p):  QWidget(p), grafico(nullptr), modifica(nullptr), creazione(nullptr)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QGridLayout* menu = new QGridLayout();

        layout->addLayout(menu);
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

        QPushButton* create = new QPushButton("Crea");
        menu->addWidget(create, 0, 3, 1, 1);
        connect(create, &QPushButton::pressed, this, &homePanel::StartCreate);
        connect(this, &homePanel::StartCreate, this, &homePanel::Create);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        menu->addItem(spacer, 0, 4, 1, 1);

        mod = new modello();
        barraRicerca = new searchBarPanel(mod->getInsiemeSens());// barra di ricerca
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
            barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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

        QString filePath = QFileDialog::getOpenFileName(this, tr("Apri file JSON"), "", tr("File JSON (*.json)"));

        if (filePath.isEmpty()) {
            return;
        }

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile aprire il file: ") + file.errorString());
            return;
        }
        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isObject()) {
            QMessageBox::warning(this, tr("Errore"), tr("Il file non contiene un oggetto JSON valido."));
            return;
        }

        QJsonObject rootObject = jsonDoc.object();
        QString sensorName;
        QJsonObject sensorObject;
        Sensore* s;
        for(auto it = rootObject.begin(); it != rootObject.end(); ++it)
        {
            sensorName = it.key();
            sensorObject = it.value().toObject();
            s = createSensorFromJson(sensorName, sensorObject);

            if (s) {
                mod->aggiungiSens(s);
            }
        }
        QMessageBox::information(this, tr("Successo"), tr("Sensori caricati con successo!"));
        if(barraRicerca)
        {
            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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

        if (filePath.isEmpty()) {
            return;
        }
        if (!filePath.endsWith(".json", Qt::CaseInsensitive)) {
            filePath += ".json";
        }

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile creare il file: ") + file.errorString());
            return;
        }

        QJsonObject jsonObject;
        for (Sensore* sensore : mod->getInsiemeSens()) {
            QJsonObject sensorObject;
            sensorObject["name"] = QString::fromStdString(sensore->getNome());
            sensorObject["type"] = QString::fromStdString(sensore->getTipo());
            sensorObject["description"] = QString::fromStdString(sensore->getDescrizione());
            QJsonArray valuesArray;
            for (double value : sensore->getValori()) {
                valuesArray.append(value);
            }
            sensorObject["values"] = valuesArray;
            sensorObject["valueMin"] = sensore->getMin();
            sensorObject["valueMax"] = sensore->getMax();

            SensorInfoVisitor visit;
            QJsonObject* p = &sensorObject;
            sensore->acceptSave(visit,p);

            jsonObject[sensore->getNome().c_str()] = sensorObject;
        }
        QJsonDocument jsonDoc(jsonObject);

        file.write(jsonDoc.toJson());
        file.close();

        QMessageBox::information(this, tr("Successo"), tr("Dati salvati nel file JSON: ") + filePath);
    }

    Sensore* homePanel::createSensorFromJson(const QString& sensorName, const QJsonObject& sensorObject) {
        QString name = sensorObject["name"].toString();
        QString type = sensorObject["type"].toString();
        QString description = sensorObject["description"].toString();
        double valueMin = sensorObject["valueMin"].toDouble();
        double valueMax = sensorObject["valueMax"].toDouble();

        if (sensorName == "SensoreConsumo" || sensorName == "Sensore Consumo") {
            double ottano = sensorObject["ottano"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreConsumo(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, ottano);
        }

        else if (sensorName == "SensoreGas" || sensorName == "Sensore Gas") {
            double footprint = sensorObject["footprint"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreGas(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, footprint);
        }

        else if (sensorName == "SensoreMotore" || sensorName == "Sensore Motore") {
            double cavalli = sensorObject["cavalli"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreMotore(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, cavalli);
        }

        else if (sensorName == "SensorePneumatico" || sensorName == "Sensore Pneumatico") {
            QString brand = sensorObject["brand"].toString();
            double age = sensorObject["age"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensorePneumatico(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, brand.toStdString(), age);
        }

        else if (sensorName == "SensoreBatteria" || sensorName == "Sensore Batteria"){
            QString materials = sensorObject["materials"].toString();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreBatteria(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, materials.toStdString());
        }
        return nullptr;
    }

    std::vector<double> homePanel::parseJsonArray(const QJsonArray& jsonArray) {
        std::vector<double> values;
        for (const QJsonValue& value : jsonArray)
        {
            if (value.isDouble())
            {
                values.push_back(value.toDouble());
            }
        }
        return values;
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
        barraRicerca = new searchBarPanel(mod->getInsiemeSens());
        connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);

        creazione = new QWidget();
        QVBoxLayout* createLayout = new QVBoxLayout(creazione);

        QLabel* labeltitle = new QLabel("Creazione di un Sensore");
        labeltitle->setAlignment(Qt::AlignCenter);
        labeltitle->setStyleSheet("font: bold 14px;");
        createLayout->addWidget(labeltitle);

        QLabel* labeltype = new QLabel("Tipologia:");
        QLineEdit* lineType = new QLineEdit(creazione);

        QLabel* labeldescr = new QLabel("Descrizione:");
        QLineEdit* lineDescr = new QLineEdit(creazione);

        QLabel* labelmin = new QLabel("Valore Min:");
        QLineEdit* lineMin = new QLineEdit(creazione);

        QLabel* labelmax = new QLabel("Valore Max:");
        QLineEdit* lineMax = new QLineEdit(creazione);

        QLabel* labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit* lineVal = new QLineEdit(creazione);

        createLayout->addWidget(labeltype);
        createLayout->addWidget(lineType);
        createLayout->addWidget(labeldescr);
        createLayout->addWidget(lineDescr);
        createLayout->addWidget(labelmin);
        createLayout->addWidget(lineMin);
        createLayout->addWidget(labelmax);
        createLayout->addWidget(lineMax);
        createLayout->addWidget(labelval);
        createLayout->addWidget(lineVal);

        QLabel* labelbox = new QLabel("Scegli il tipo del Sensore:");
        createLayout->addWidget(labelbox);

        QComboBox* sensorTypeComboBox = new QComboBox();
        sensorTypeComboBox->addItem("Sensore Consumo");
        sensorTypeComboBox->addItem("Sensore Motore");
        sensorTypeComboBox->addItem("Sensore Batteria");
        sensorTypeComboBox->addItem("Sensore Gas");
        sensorTypeComboBox->addItem("Sensore Pneumatico");

        createLayout->addWidget(sensorTypeComboBox);

        connect(sensorTypeComboBox, QOverload<int>::of(&QComboBox::activated), [=](int index) {
                QString selectedOption = sensorTypeComboBox->itemText(index);
                emit StartSensorSelected(lineType, lineDescr, lineMin, lineMax, lineVal, selectedOption, createLayout); });

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

                QString numString = lineVal->text();
                std::vector<double> valArray;
                QStringList input = numString.trimmed().split(" ");
                foreach(QString numString, input)
                {
                    bool conversionOk;
                    int num = numString.toDouble(&conversionOk);
                    if(conversionOk)
                    {
                        valArray.push_back(num);
                    }
                    else
                    {
                        std::cerr << "Errore durante la conversione di " << numString.toStdString() << " in double." << std::endl;
                    }
                }
                Sensore* sensore = new SensoreBatteria(selectedSensor.toStdString(), lineType->text().toStdString(), lineDescr->text().toStdString(), valArray,
                                                           lineMin->text().toDouble(), lineMax->text().toDouble(), lineMat->text().toStdString());

                mod->aggiungiSens(sensore);

                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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

                QString numString = lineVal->text();
                std::vector<double> valArray;
                QStringList input = numString.trimmed().split(" ");
                foreach(QString numString, input)
                {
                    bool conversionOk;
                    int num = numString.toDouble(&conversionOk);
                    if(conversionOk)
                    {
                        valArray.push_back(num);
                    }
                    else
                    {
                        std::cerr << "Errore durante la conversione di " << numString.toStdString() << " in double." << std::endl;
                    }
                }
                Sensore* sensore = new SensoreConsumo(selectedSensor.toStdString(), lineType->text().toStdString(), lineDescr->text().toStdString(), valArray,
                                                               lineMin->text().toDouble(), lineMax->text().toDouble(), lineOtt->text().toInt());

                mod->aggiungiSens(sensore);

                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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

                QString numString = lineVal->text();
                std::vector<double> valArray;
                QStringList input = numString.trimmed().split(" ");
                foreach(QString numString, input)
                {
                    bool conversionOk;
                    int num = numString.toDouble(&conversionOk);
                    if(conversionOk)
                    {
                        valArray.push_back(num);
                    }
                    else
                    {
                        std::cerr << "Errore durante la conversione di " << numString.toStdString() << " in double." << std::endl;
                    }
                }
                Sensore* sensore = new SensoreMotore(selectedSensor.toStdString(), lineType->text().toStdString(), lineDescr->text().toStdString(), valArray,
                                                               lineMin->text().toDouble(), lineMax->text().toDouble(), lineCav->text().toUInt());

                mod->aggiungiSens(sensore);

                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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

                QString numString = lineVal->text();
                std::vector<double> valArray;
                QStringList input = numString.trimmed().split(" ");
                foreach(QString numString, input)
                {
                    bool conversionOk;
                    int num = numString.toDouble(&conversionOk);
                    if(conversionOk)
                    {
                        valArray.push_back(num);
                    }
                    else
                    {
                        std::cerr << "Errore durante la conversione di " << numString.toStdString() << " in double." << std::endl;
                    }
                }
                Sensore* sensore = new SensoreGas(selectedSensor.toStdString(), lineType->text().toStdString(), lineDescr->text().toStdString(), valArray,
                                                               lineMin->text().toDouble(), lineMax->text().toDouble(), lineFootp->text().toDouble());

                mod->aggiungiSens(sensore);

                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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

                QString numString = lineVal->text();
                std::vector<double> valArray;
                QStringList input = numString.trimmed().split(" ");
                foreach(QString numString, input)
                {
                    bool conversionOk;
                    int num = numString.toDouble(&conversionOk);
                    if(conversionOk)
                    {
                        valArray.push_back(num);
                    }
                    else
                    {
                        std::cerr << "Errore durante la conversione di " << numString.toStdString() << " in double." << std::endl;
                    }
                }
                Sensore* sensore = new SensorePneumatico(selectedSensor.toStdString(), lineType->text().toStdString(), lineDescr->text().toStdString(), valArray,
                                                               lineMin->text().toDouble(), lineMax->text().toDouble(), lineBr->text().toStdString(), lineAge->text().toDouble());

                mod->aggiungiSens(sensore);

                if(barraRicerca)
                {
                    delete barraRicerca;
                    delete creazione;
                    creazione = nullptr;
                    barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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
            });
        }
    }

    void homePanel::Modify(Sensore *s){
        if (grafico) {
            this->pannello->layout()->removeWidget(grafico);
            delete grafico;
            grafico = nullptr;
        }
        if(modifica){
            this->pannello->layout()->removeWidget(modifica);
            delete modifica;
            modifica = nullptr;
        }

        modifica = new QWidget();

        QVBoxLayout* modLayout = new QVBoxLayout(modifica);

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

        std::string type = s->getTipo();
        std::string descr = s->getDescrizione();
        double min = s->getMin();
        double max = s->getMax();
        std::vector<double> v = s->getValori();

        QString qtype = QString::fromStdString(type);
        QString qdescr = QString::fromStdString(descr);
        QString qmin = QString::number(min);
        QString qmax = QString::number(max);
        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(qtype);
        lineDescr->setText(qdescr);
        lineMin->setText(qmin);
        lineMax->setText(qmax);
        lineVal->setText(qval);

        modLayout->addWidget(lineType);
        modLayout->addWidget(lineDescr);
        modLayout->addWidget(lineMin);
        modLayout->addWidget(lineMax);
        modLayout->addWidget(lineVal);

        int fieldWidth = this->pannello->width() /3;
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);

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

        QPushButton *confirmButton = new QPushButton("Conferma", this->pannello);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        connect(confirmButton, &QPushButton::pressed, this, [this, s, lineType, lineDescr, lineVal, lineMin, lineMax]() {
            emit StartUpdate(s, lineType, lineDescr, lineVal, lineMin, lineMax);
        });
        connect(this, &homePanel::StartUpdate, this, &homePanel::Update);

        QPushButton *exitButton = new QPushButton("Annulla", this->pannello);
        modLayout->addWidget(exitButton, 0, Qt::AlignLeft);
        connect(exitButton, &QPushButton::pressed, this, &homePanel::StartExit);
        connect(this, &homePanel::StartExit, this, &homePanel::Exit);

        pannello->layout()->addWidget(modifica);
    }

    void homePanel::Update(Sensore *s, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * max){
        s->setTipo(tipo->text().toStdString());
        s->setDescrizione(descrizione->text().toStdString());
        QString numString = val->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            int num = numString.toDouble(&conversionOk);
            if(conversionOk)
            {
                valArray.push_back(num);
            }
            else
            {
                std::cerr << "Errore durante la conversione di " << numString.toStdString() << " in double." << std::endl;
            }
        }
        s->setValori(valArray);
        s->setMin(min->text().toDouble());
        s->setMax(max->text().toDouble());

        if(modifica){
            this->pannello->layout()->removeWidget(modifica);
            delete modifica;
            modifica = nullptr;

            delete barraRicerca;
            barraRicerca = new searchBarPanel(mod->getInsiemeSens());
            delete pannello;
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

    void homePanel::Simulation(){
        if (grafico) {
            this->pannello->layout()->removeWidget(grafico);
            delete grafico;
            grafico = nullptr;
        }
        if(modifica){
            this->pannello->layout()->removeWidget(modifica);
            delete modifica;
            modifica = nullptr;
        }
        QSplineSeries *series = new QSplineSeries();
        std::vector<double> valori = sensoreGenerale->getValori();

        std::vector<int> xAxisValues;
        int xValue = 1;
        for (auto it = valori.begin(); it != valori.end(); ++it) {
            series->append(xValue++, *it);
        }

        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->legend()->hide();
        chart->setTitle("" + QString::fromStdString(sensoreGenerale->getTipo()) + " di: " + QString::fromStdString(sensoreGenerale->getNome()));

        // Asse X
        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(1, valori.size());
        axisX->setTickCount(valori.size());
        axisX->setLabelFormat("%d");
        chart->addAxis(axisX, Qt::AlignBottom);

        // Asse Y
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(sensoreGenerale->getMin(), sensoreGenerale->getMax());
        axisY->setTickCount(10);
        axisY->applyNiceNumbers();
        chart->addAxis(axisY, Qt::AlignLeft);

        series->attachAxis(axisX);
        series->attachAxis(axisY);

        grafico = new QChartView(chart);
        grafico->setRenderHint(QPainter::Antialiasing);
        this->pannello->layout()->addWidget(grafico);

    }

    void homePanel::Exit(){
        if(modifica){
            this->pannello->layout()->removeWidget(modifica);
            delete modifica;
            modifica = nullptr;
        }
    }

    void homePanel::Elimination(Sensore* s) {
        if(modifica)
            modifica = nullptr;
        if(grafico)
            grafico = nullptr;
        std::vector<Sensore*> v = mod->getInsiemeSens();
        mod->eliminaSens(s);
        sensoreGenerale = nullptr;
        s = nullptr;
        if(pannello)
        {
            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(mod->getInsiemeSens());
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


    void homePanel::View(Sensore* s){ 
        if(pannello)
        {
            this->layout()->removeWidget(pannello);
            if(grafico)
                grafico = nullptr;
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
