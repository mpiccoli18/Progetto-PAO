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
            QPushButton* conferma;

        public:
            QWidget* getWidget();
            QPushButton* getPulsante();
            void setModello(modello* m);
            virtual void visitaSPneumatico(SensorePneumatico& sPneumatico);
            virtual void visitaSConsumo(SensoreConsumo& sConsumo);
            virtual void visitaSMotore(SensoreMotore& sMotore);
            virtual void visitaSBatteria(SensoreBatteria& sBatteria);
            virtual void visitaSGas(SensoreGas& sGas);

            virtual void modSPneumatico(SensorePneumatico* sPneumatico);
            virtual void modSConsumo(SensoreConsumo* sConsumo);
            virtual void modSMotore(SensoreMotore* sMotore);
            virtual void modSBatteria(SensoreBatteria* sBatteria);
            virtual void modSGas(SensoreGas* sGas);

            virtual void salvaSPneumatico(SensorePneumatico& sPneumatico, QJsonObject* ob);
            virtual void salvaSConsumo(SensoreConsumo& sConsumo,QJsonObject* ob);
            virtual void salvaSMotore(SensoreMotore& sMotore,QJsonObject* ob);
            virtual void salvaSBatteria(SensoreBatteria& sBatteria,QJsonObject* ob);
            virtual void salvaSGas(SensoreGas& sGas,QJsonObject* ob);
    };

}

#endif // SENSORINFOVISITOR_H
