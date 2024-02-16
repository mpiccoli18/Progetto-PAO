#include "homePanel.h"
#include "SensorInfoVisitor.h"
#include <QString>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QtCharts>
#include <QLineEdit>
#include <iostream>
#include <vector>

namespace sensore{
homePanel::homePanel(QWidget* p):  QWidget(p), chartView(nullptr), modifyView(nullptr)
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
        connect(this, &homePanel::StartClose, this, &homePanel::Close);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        menu->addItem(spacer, 0, 4, 1, 1);

        barraRicerca = new searchBarPanel(InsiemeSensori);//barra
        layoutApp->addWidget(barraRicerca,1);

        pannello = new SensorPanel();//sensore
        layoutApp->addWidget(pannello,2);

        layoutApp->setStretch(0, 1);
        layoutApp->setStretch(1, 2);

        connect(barraRicerca, &searchBarPanel::StartView, this, &homePanel::View);
        connect(pannello, &SensorPanel::StartElimination, this, &homePanel::Elimination);
    }

    void homePanel::Save(){
        QString filePath = QFileDialog::getSaveFileName(this, tr("Salva file JSON"), "", tr("File JSON (.json)"));

        if (filePath.isEmpty()) {
            // Nessun percorso specificato per il file JSON, esci senza fare nulla
            return;
        }

        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly)) {
            // Errore nell'apertura del file per la scrittura
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile creare il file: ") + file.errorString());
            return;
        }

        // Crea un oggetto JSON contenente i dati degli oggetti sensori
        QJsonObject jsonObject;
        for (Sensore* sensore : InsiemeSensori) {
            QJsonObject sensorObject;
            sensorObject["name"] = QString::fromStdString(sensore->getName());
            sensorObject["type"] = QString::fromStdString(sensore->getType());
            sensorObject["description"] = QString::fromStdString(sensore->getDescription());
            QJsonArray valuesArray;
            for (double value : sensore->getValues()) {
                valuesArray.append(value);
            }
            sensorObject["values"] = valuesArray;
            sensorObject["valueMin"] = sensore->getValueMin();
            sensorObject["valueMax"] = sensore->getValueMax();

            // Utilizza il SensorInfoVisitor per ottenere i dettagli aggiuntivi del sensore
            SensorInfoVisitor visitor;
            sensore->accept(visitor);
            QWidget* sensorWidget = visitor.getWidget();
            // Ottieni i dettagli aggiuntivi dal widget e aggiungili all'oggetto JSON del sensore
            if (sensorWidget) {
                QLayoutItem* layoutItem = sensorWidget->layout()->itemAt(1); // Assumendo che il widget contenga un layout con il dettaglio
                if (layoutItem) {
                    QLabel* detailLabel = qobject_cast<QLabel*>(layoutItem->widget());
                    if (detailLabel) {
                        QString detailText = detailLabel->text();
                        QString detailType = detailText.split(":").first().trimmed();
                        QString detailValue = detailText.split(":").last().trimmed();
                        sensorObject[detailType] = detailValue;
                    }
                }
            }

            // Aggiungi l'oggetto sensore all'oggetto JSON principale
            jsonObject[sensore->getName().c_str()] = sensorObject;
        }

        // Serializza l'oggetto JSON in un documento JSON
        QJsonDocument jsonDoc(jsonObject);

        // Scrivi il documento JSON nel file
        file.write(jsonDoc.toJson());

        // Chiudi il file
        file.close();

        // Informa l'utente del successo
        QMessageBox::information(this, tr("Successo"), tr("Dati salvati nel file JSON: ") + filePath);
    }

    void homePanel::Open(){
        // Apre una finestra di dialogo per la selezione del file JSON
        QString filePath = QFileDialog::getOpenFileName(this, tr("Apri file JSON"), "", tr("File JSON (*.json)"));

        if (filePath.isEmpty()) {
            // L'utente ha annullato la selezione del file
            return;
        }

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)) {
            // Errore nell'apertura del file
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile aprire il file: ") + file.errorString());
            return;
        }

        // Legge il contenuto del file JSON
        QByteArray jsonData = file.readAll();
        file.close();

        // Converte il JSON
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isObject()) {
            QMessageBox::warning(this, tr("Errore"), tr("Il file non contiene un oggetto JSON valido."));
            return;
        }

        // Ottiene l'oggetto radice del JSON
        QJsonObject rootObject = jsonDoc.object();
        QString sensorName;
        QJsonObject sensorObject;
        Sensore* s;
            // Itera su tutti i sensori nel JSON e crea gli oggetti Sensore corrispondenti
            for (auto it = rootObject.begin(); it != rootObject.end(); ++it)
            {
                sensorName = it.key();
                sensorObject = it.value().toObject();
                s = createSensorFromJson(sensorName, sensorObject);
                // Aggiunge il sensore al vettore InsiemeSensori
                if (s) {
                    InsiemeSensori.push_back(s);
                }
            }

        // Ora hai caricato con successo i sensori dal file JSON
        QMessageBox::information(this, tr("Successo"), tr("Sensori caricati con successo!"));
        if(barraRicerca)
        {
            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(InsiemeSensori);
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

    Sensore* homePanel::createSensorFromJson(const QString& sensorName, const QJsonObject& sensorObject) {
        QString name = sensorObject["name"].toString();
        QString type = sensorObject["type"].toString();
        QString description = sensorObject["description"].toString();
        double valueMin = sensorObject["valueMin"].toDouble();
        double valueMax = sensorObject["valueMax"].toDouble();

        // Controlla il nome del sensore e crea l'oggetto corrispondente
        if (sensorName == "SensoreConsumo") {
            // Esempio di creazione di SensoreConsumo
            double ottano = sensorObject["ottano"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreConsumo(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, ottano);
        }

        else if (sensorName == "SensoreGas") {
            // Esempio di creazione di SensoreGas
            double footprint = sensorObject["footprint"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreGas(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, footprint);
        }

        else if (sensorName == "SensoreMotore") {
            // Esempio di creazione di SensoreMotore
            double cavalli = sensorObject["cavalli"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreMotore(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, cavalli);
        }

        else if (sensorName == "SensorePneumatico") {
            // Esempio di creazione di SensorePneumatico
            QString brand = sensorObject["brand"].toString();
            double age = sensorObject["age"].toDouble();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensorePneumatico(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, brand.toStdString(), age);
        }

        else if (sensorName == "SensoreBatteria"){
            // Esempio di creazione di SensoreBatteria
            QString materials = sensorObject["materials"].toString();
            std::vector<double> values = parseJsonArray(sensorObject["values"].toArray());
            return new SensoreBatteria(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, materials.toStdString());
        }

        // Se il nome del sensore non è riconosciuto, restituisci nullptr
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

    void homePanel::Close(){ // piu avanti

    }

    void homePanel::Modify(Sensore *s){
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
        std::string name = s->getName();
        std::string type = s->getType();
        std::string descr = s->getDescription();
        double min = s->getValueMin();
        double max = s->getValueMax();
        std::vector<double> v = s->getValues();

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
        s->acceptModify(visitor);
        modLayout->addWidget(visitor.getWidget());

        // Aggiungi pulsante di conferma
        QPushButton *confirmButton = new QPushButton("Conferma", this->pannello);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        connect(confirmButton, &QPushButton::pressed, this, [this, s, lineName, lineType, lineDescr, lineVal, lineMin, lineMax]() {
            emit StartUpdate(s, lineName, lineType, lineDescr, lineVal, lineMin, lineMax); }); // sistemare
        connect(this, &homePanel::StartUpdate, this, &homePanel::Update);

        QPushButton *exitButton = new QPushButton("Annulla", this->pannello);
        modLayout->addWidget(exitButton, 0, Qt::AlignLeft);
        connect(exitButton, &QPushButton::pressed, this, &homePanel::StartExit);
        connect(this, &homePanel::StartExit, this, &homePanel::Exit);

        // Aggiungi il widget con i campi di input e il pulsante al layout del pannello
        this->pannello->layout()->addWidget(modifyView);
    }

    void homePanel::Update(Sensore *s, QLineEdit * nome, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * Max){
        s->setName(nome->text().toStdString());
        s->setType(tipo->text().toStdString());
        s->setDescription(descrizione->text().toStdString());
        QString numString = val->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            int num = numString.toInt(&conversionOk);
            if(conversionOk)
            {
                valArray.push_back(num);
            }
            else
            {
                std::cerr << "Errore durante la conversione di " << numString.toStdString() << " in intero." << std::endl;
            }
        }
        s->setValues(valArray);
        s->setValueMin(min->text().toDouble());
        s->setValueMax(Max->text().toDouble());
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
        axisX->setRange(1, valori.size());
        axisX->setTickCount(valori.size());
        grafico->addAxis(axisX, Qt::AlignBottom);

        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(sensoreGenerale->getValueMin(), sensoreGenerale->getValueMax());
        axisY->setTickCount(valori.size());
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

    void homePanel::Elimination(Sensore* s) {
        if(modifyView)
            modifyView = nullptr;
        if(chartView)
            chartView = nullptr;
        for(auto i = InsiemeSensori.begin(); i != InsiemeSensori.end();)
        {
            if(*i == s)
            {
                delete *i;
                InsiemeSensori.erase(i);
            }
            else{
                i++;
            }
        }
        sensoreGenerale = nullptr;
        s = nullptr;
        if(pannello)
        {
            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(InsiemeSensori);
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
