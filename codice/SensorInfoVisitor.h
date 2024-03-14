#ifndef SENSORINFOVISITOR_H
#define SENSORINFOVISITOR_H

#include <QWidget>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include "SensorVisitorInterface.h"
#include "sensorePneumatico.h"
#include "sensoreConsumo.h"
#include "sensoreMotore.h"
#include "sensoreBatteria.h"
#include "sensoreGas.h"

namespace sensore{
    class modello;

    class SensorInfoVisitor : public SensorVisitorInterface {
        private:
            QWidget* widget;
            modello* mod;
            QPushButton* confirmButton;

        public:
            QWidget* getWidget();
            QPushButton* getButton();
            void setModello(modello* m);
            virtual void visitSPneumatico(SensorePneumatico& sPneumatico);
            virtual void visitSConsumo(SensoreConsumo& sConsumo);
            virtual void visitSMotore(SensoreMotore& sMotore);
            virtual void visitSBatteria(SensoreBatteria& sBatteria);
            virtual void visitSGas(SensoreGas& sGas);

            virtual void modSPneumatico(SensorePneumatico* sPneumatico);
            virtual void modSConsumo(SensoreConsumo* sConsumo);
            virtual void modSMotore(SensoreMotore* sMotore);
            virtual void modSBatteria(SensoreBatteria* sBatteria);
            virtual void modSGas(SensoreGas* sGas);

            virtual void saveSPneumatico(SensorePneumatico& sPneumatico, QJsonObject* ob);
            virtual void saveSConsumo(SensoreConsumo& sConsumo,QJsonObject* ob);
            virtual void saveSMotore(SensoreMotore& sMotore,QJsonObject* ob);
            virtual void saveSBatteria(SensoreBatteria& sBatteria,QJsonObject* ob);
            virtual void saveSGas(SensoreGas& sGas,QJsonObject* ob);
    };

}

#endif // SENSORINFOVISITOR_H
