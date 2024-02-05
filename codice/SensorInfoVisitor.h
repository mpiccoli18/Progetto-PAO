#ifndef SENSORINFOVISITOR_H
#define SENSORINFOVISITOR_H

#include <QWidget>
#include "SensorVisitorInterface.h"

namespace sensore{

    class SensorInfoVisitor: public sensore::SensorVisitorInterface {
        private:
            QWidget* widget;

        public:
            QWidget* getWidget();
            virtual void visitSPneumatico(SensorePneumatico& sPneumatico);
            virtual void visitSConsumo(SensoreConsumo& sConsumo);
            virtual void visitSMotore(SensoreMotore& sMotore);
            virtual void visitSBatteria(SensoreBatteria& sBatteria);
            virtual void visitSGas(SensoreGas& sGas);
    };

}

#endif // SENSORINFOVISITOR_H
