#ifndef SENSORINFOVISITOR_H
#define SENSORINFOVISITOR_H

#include <QWidget>
#include "SensorVisitorInterface.h"

namespace sensore{

    class SensorInfoVisitor: public sensore::SensorVisitorInterface {
        private:
            QWidget* widget;
            std::vector<QLineEdit*> aus;

        public:
            QWidget* getWidget();
            virtual void visitSPneumatico(SensorePneumatico& sPneumatico);
            virtual void visitSConsumo(SensoreConsumo& sConsumo);
            virtual void visitSMotore(SensoreMotore& sMotore);
            virtual void visitSBatteria(SensoreBatteria& sBatteria);
            virtual void visitSGas(SensoreGas& sGas);

            virtual std::vector<QLineEdit*> modSPneumatico(SensorePneumatico& sPneumatico);
            virtual std::vector<QLineEdit*> modSConsumo(SensoreConsumo& sConsumo);
            virtual std::vector<QLineEdit*> modSMotore(SensoreMotore& sMotore);
            virtual std::vector<QLineEdit*> modSBatteria(SensoreBatteria& sBatteria);
            virtual std::vector<QLineEdit*> modSGas(SensoreGas& sGas);

            virtual void saveSPneumatico(SensorePneumatico& sPneumatico, QJsonObject* ob);
            virtual void saveSConsumo(SensoreConsumo& sConsumo,QJsonObject* ob);
            virtual void saveSMotore(SensoreMotore& sMotore,QJsonObject* ob);
            virtual void saveSBatteria(SensoreBatteria& sBatteria,QJsonObject* ob);
            virtual void saveSGas(SensoreGas& sGas,QJsonObject* ob);
    };

}

#endif // SENSORINFOVISITOR_H
