#ifndef MODELLO_H
#define MODELLO_H
#include "sensore.h"
#include <vector>

namespace sensore{
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
            void creaSensGas(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineImp);
            void creaSensMotore(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineCav);
            void creaSensPneumatico(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineEta, QLineEdit* lineMarca);
            void creaSensBatteria(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineMat);
            void creaSensConsumo(const QString& selectedSensor, QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, QLineEdit* lineOtt);
    };
}
#endif // MODELLO_H
