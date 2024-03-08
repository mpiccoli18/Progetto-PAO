#include "modello.h"
#include "sensoreBatteria.h"
#include "sensoreConsumo.h"
#include "sensorePneumatico.h"
#include "sensoreGas.h"
#include "sensoreMotore.h"
#include "SensorInfoVisitor.h"
#include <iostream>
#include <QFileDialog>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonArray>

namespace sensore{
    modello::modello(){};

    std::vector<sensore::Sensore*> modello::getInsiemeSens() const{
        std::vector<Sensore*> sens;
        if(!InsiemeSensori.empty())
        {
            for(int i = 0; i < InsiemeSensori.size(); i++)
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
        for(int i = 0; i < InsiemeSensori.size(); i++)
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
        QString name = sensorObject["nome"].toString();
        QString type = sensorObject["tipo"].toString();
        QString description = sensorObject["descrizione"].toString();
        double valueMin = sensorObject["minimo"].toDouble();
        double valueMax = sensorObject["massimo"].toDouble();

        if (sensorName == "SensoreConsumo" || sensorName == "Sensore Consumo") {
            double ottano = sensorObject["ottano"].toDouble();
            std::vector<double> values = daJsonAdArray(sensorObject["valori"].toArray());
            return new SensoreConsumo(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, ottano);
        }

        else if (sensorName == "SensoreGas" || sensorName == "Sensore Gas") {
            double footprint = sensorObject["impronta"].toDouble();
            std::vector<double> values = daJsonAdArray(sensorObject["valori"].toArray());
            return new SensoreGas(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, footprint);
        }

        else if (sensorName == "SensoreMotore" || sensorName == "Sensore Motore") {
            double cavalli = sensorObject["cavalli"].toDouble();
            std::vector<double> values = daJsonAdArray(sensorObject["valori"].toArray());
            return new SensoreMotore(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, cavalli);
        }

        else if (sensorName == "SensorePneumatico" || sensorName == "Sensore Pneumatico") {
            QString brand = sensorObject["marca pneumatico"].toString();
            double age = sensorObject["eta"].toDouble();
            std::vector<double> values = daJsonAdArray(sensorObject["valori"].toArray());
            return new SensorePneumatico(name.toStdString(), type.toStdString(), description.toStdString(), values, valueMin, valueMax, brand.toStdString(), age);
        }

        else if (sensorName == "SensoreBatteria" || sensorName == "Sensore Batteria"){
            QString materials = sensorObject["materiale"].toString();
            std::vector<double> values = daJsonAdArray(sensorObject["valori"].toArray());
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
        for (Sensore* sensore : getInsiemeSens()) {
            QJsonObject sensorObject;
            sensorObject["nome"] = QString::fromStdString(sensore->getNome());
            sensorObject["tipo"] = QString::fromStdString(sensore->getTipo());
            sensorObject["descrizione"] = QString::fromStdString(sensore->getDescrizione());
            QJsonArray valuesArray;
            for (double value : sensore->getValori()) {
                valuesArray.append(value);
            }
            sensorObject["valori"] = valuesArray;
            sensorObject["minimo"] = sensore->getMin();
            sensorObject["massimo"] = sensore->getMax();

            SensorInfoVisitor visit;
            QJsonObject* p = &sensorObject;
            sensore->acceptSave(visit,p);

            jsonObject[sensore->getNome().c_str()] = sensorObject;
        }
        QJsonDocument jsonDoc(jsonObject);

        file.write(jsonDoc.toJson());
        file.close();
        return 3;
    }

    void modello::creaSensGas(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineImp){
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
                                             lineMin->text().toDouble(), lineMax->text().toDouble(), lineImp->text().toDouble());
        aggiungiSens(sensore);
    }

    void modello::creaSensMotore(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineCav){
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
        aggiungiSens(sensore);
    }

    void modello::creaSensPneumatico(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineEta, QLineEdit* lineMarca){
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
                                             lineMin->text().toDouble(), lineMax->text().toDouble(), lineMarca->text().toStdString(), lineEta->text().toDouble());
        aggiungiSens(sensore);
    }

    void modello::creaSensBatteria(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineMat){
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
        aggiungiSens(sensore);
    }

    void modello::creaSensConsumo(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineOtt){
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
                                             lineMin->text().toDouble(), lineMax->text().toDouble(), lineOtt->text().toUInt());
        aggiungiSens(sensore);
    }
}


