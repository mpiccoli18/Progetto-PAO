#include "modello.h"
#include "SensorInfoVisitor.h"

namespace sensore{
    modello::modello(){};

    std::vector<sensore::Sensore*> modello::getInsiemeSens() const{
        std::vector<Sensore*> sens;
        if(!InsiemeSensori.empty())
        {
            for(unsigned long long i = 0; i < InsiemeSensori.size(); i++)
            {
                sens.push_back(InsiemeSensori[i]);
            }
        }
        return sens;
    };

    void modello::aggiungiSens(Sensore* s){
        InsiemeSensori.push_back(s);
    };

    void modello::eliminaSens(Sensore* s){
        auto j = InsiemeSensori.begin();
        for(unsigned long long i = 0; i < InsiemeSensori.size(); i++)
        {
            if(InsiemeSensori[i] == s)
            {
                InsiemeSensori.erase(j);
            }
            else
            {
                j++;
            }
        }
    };

    int modello::apriSens(QString doc){
        if (doc.isEmpty()) {
            return 1;
        }

        QFile file(doc);
        if (!file.open(QIODevice::ReadOnly)) {
            return 2;
        }

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        if (!jsonDoc.isObject()) {
            return 3;
        }

        QJsonObject rootObject = jsonDoc.object();
        QString sensorName;
        QJsonObject sensorObject;
        Sensore* s;
        for(auto it = rootObject.begin(); it != rootObject.end(); ++it)
        {
            sensorName = it.key();
            sensorObject = it.value().toObject();
            s = creaSensDaJson(sensorName, sensorObject);

            if (s) {
                aggiungiSens(s);
            }
        }
        return 4;
    }

    Sensore* modello::creaSensDaJson(const QString& sensorName, const QJsonObject& sensorObject) {
        QString name = sensorObject["Nome"].toString();
        QString type = sensorObject["Tipo"].toString();
        QString description = sensorObject["Descrizione"].toString();
        double valueMin = sensorObject["Minimo"].toDouble();
        double valueMax = sensorObject["Massimo"].toDouble();

        if (sensorName == "SensoreConsumo" || sensorName == "Sensore Consumo" || sensorName.contains("Sensore Consumo")) {
            QString ott = sensorObject["Ottano"].toString();
            double ottano = ott.toUInt();
            std::vector<double> values = daJsonAdArray(sensorObject["Valori"].toArray());
            return new SensoreConsumo(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, ottano);
        }

        else if (sensorName == "SensoreGas" || sensorName == "Sensore Gas" || sensorName.contains("Sensore Gas")) {
            QString footprint = sensorObject["Impronta"].toString();
            double impronta = footprint.toDouble();
            std::vector<double> values = daJsonAdArray(sensorObject["Valori"].toArray());
            return new SensoreGas(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, impronta);
        }

        else if (sensorName == "SensoreMotore" || sensorName == "Sensore Motore" || sensorName.contains("Sensore Motore")) {
            QString hv = sensorObject["Cavalli"].toString();
            double cavalli = hv.toDouble();
            std::vector<double> values = daJsonAdArray(sensorObject["Valori"].toArray());
            return new SensoreMotore(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, cavalli);
        }

        else if (sensorName == "SensorePneumatico" || sensorName == "Sensore Pneumatico" || sensorName.contains("Sensore Pneumatico")) {
            QString brand = sensorObject["Marca Pneumatico"].toString();
            QString age = sensorObject["Eta Pneumatico"].toString();
            double eta = age.toDouble();
            std::vector<double> values = daJsonAdArray(sensorObject["Valori"].toArray());
            return new SensorePneumatico(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, brand.toStdString(), eta);
        }

        else if (sensorName == "SensoreBatteria" || sensorName == "Sensore Batteria" || sensorName.contains("Sensore Batteria")){
            QString materials = sensorObject["Materiale"].toString();
            std::vector<double> values = daJsonAdArray(sensorObject["Valori"].toArray());
            return new SensoreBatteria(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, materials.toStdString());
        }
        return nullptr;
    }

    std::vector<double> modello::daJsonAdArray(const QJsonArray& jsonArray) {
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

    int modello::salvaSens(QString doc)
    {
        if (doc.isEmpty()) {
            return 1;
        }
        if (!doc.endsWith(".json", Qt::CaseInsensitive)) {
            doc += ".json";
        }

        QFile file(doc);
        if (!file.open(QIODevice::WriteOnly)) {
            return 2;
        }

        QJsonObject jsonObject;
        Sensore* sensore;
        int j = 1;
        for (auto i = InsiemeSensori.begin(); i != InsiemeSensori.end(); i++) {
            sensore = *i;
            QJsonObject sensorObject;
            sensorObject["Nome"] = QString::fromStdString(sensore->getNome());
            sensorObject["Tipo"] = QString::fromStdString(sensore->getTipo());
            sensorObject["Descrizione"] = QString::fromStdString(sensore->getDescrizione());
            QJsonArray valuesArray;
            for (double value : sensore->getValori()) {
                valuesArray.append(value);
            }
            sensorObject["Valori"] = valuesArray;
            sensorObject["Minimo"] = sensore->getMin();
            sensorObject["Massimo"] = sensore->getMax();

            SensorInfoVisitor visit;
            QJsonObject* p = &sensorObject;
            sensore->acceptSave(visit,p);
            jsonObject[(sensore->getNome().c_str() + (QString::number(j)))] = sensorObject;
            j++;
        }
        QJsonDocument jsonDoc(jsonObject);

        file.write(jsonDoc.toJson());
        file.close();
        return 3;
}

    void modello::creaSensGas(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineImp){
        QString numString = lineVal->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            double num = numString.toDouble(&conversionOk);
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
                                             lineMin->text().toDouble(), lineMax->text().toDouble(), lineImp->text().toDouble());
        aggiungiSens(sensore);
    }

    void modello::creaSensMotore(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineCav){
        QString numString = lineVal->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            double num = numString.toDouble(&conversionOk);
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
        aggiungiSens(sensore);
    }

    void modello::creaSensPneumatico(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineEta, QLineEdit* lineMarca){
        QString numString = lineVal->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            double num = numString.toDouble(&conversionOk);
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
                                             lineMin->text().toDouble(), lineMax->text().toDouble(), lineMarca->text().toStdString(), lineEta->text().toDouble());
        aggiungiSens(sensore);
    }

    void modello::creaSensBatteria(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineMat){
        QString numString = lineVal->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            double num = numString.toDouble(&conversionOk);
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
        aggiungiSens(sensore);
    }

    void modello::creaSensConsumo(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineOtt){
        QString numString = lineVal->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            double num = numString.toDouble(&conversionOk);
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
                                             lineMin->text().toDouble(), lineMax->text().toDouble(), lineOtt->text().toUInt());
        aggiungiSens(sensore);
    }

    void modello::aggiornaSens(Sensore *s, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * max){
        s->setTipo(tipo->text().toStdString());
        s->setDescrizione(descrizione->text().toStdString());
        QString numString = val->text();
        std::vector<double> valArray;
        QStringList input = numString.trimmed().split(" ");
        foreach(QString numString, input)
        {
            bool conversionOk;
            double num = numString.toDouble(&conversionOk);
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
    }

    void modello::modificaSensorePneumatico(SensorePneumatico* s, QLineEdit * marca, QLineEdit * eta ){
        s->setMarcaPneu(marca->text().toStdString());
        s->setEta(eta->text().toDouble());
    }

    void modello::modificaSensoreGas(SensoreGas* s, QLineEdit * impronta){
        s->setImpronta(impronta->text().toDouble());
    }
    void modello::modificaSensoreMotore(SensoreMotore* s, QLineEdit * cavalli){
        s->setCavalli(cavalli->text().toUInt());
    }
    void modello::modificaSensoreBatteria(SensoreBatteria* s, QLineEdit * materiale){
         s->setMateriale(materiale->text().toStdString());
    }
    void modello::modificaSensoreConsumo(SensoreConsumo* s, QLineEdit * ottano){
        s->setOttano(ottano->text().toUInt());
    }


    void modello::pulisciInsieme(){
        InsiemeSensori.clear();
    }
}


