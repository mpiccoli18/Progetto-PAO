#ifndef MODELLO_H
#define MODELLO_H

#include <vector>
#include <iostream>
#include <QFileDialog>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonArray>
#include <QLineEdit>
#include "sensore.h"

namespace sensore{
    class SensorInfoVisitor;

    class modello{
        private:
            std::vector<sensore::Sensore*> InsiemeSensori;
        public:
            modello();
            std::vector<sensore::Sensore*> getInsiemeSens() const;
            Sensore* creaSensDaJson(const QString& sensorName, const QJsonObject& sensorObject);
            std::vector<double> daJsonAdArray(const QJsonArray& jsonArray);

            void aggiungiSens(Sensore* s);
            void eliminaSens(Sensore* s);
            int apriSens(QString doc);
            int salvaSens(QString doc);
            void creaSensGas(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineImp);
            void creaSensMotore(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineCav);
            void creaSensPneumatico(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineEta, QLineEdit* lineMarca);
            void creaSensBatteria(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineMat);
            void creaSensConsumo(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineVal, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineOtt);
            void aggiornaSens(Sensore *s, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * max);

            void modificaSensorePneumatico(SensorePneumatico* s,QLineEdit * marca, QLineEdit * eta );
            void modificaSensoreGas(SensoreGas* s,QLineEdit * impronta);
            void modificaSensoreMotore(SensoreMotore* s,QLineEdit * cavalli);
            void modificaSensoreBatteria(SensoreBatteria* s,QLineEdit * materiale);
            void modificaSensoreConsumo(SensoreConsumo* s,QLineEdit * ottano);
            void pulisciInsieme();
    };
}
#endif // MODELLO_H
