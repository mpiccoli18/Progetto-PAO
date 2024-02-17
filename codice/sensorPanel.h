#ifndef SENSORPANEL_H
#define SENSORPANEL_H

#include "Info.h"
#include "sensoreBatteria.h"
#include "sensoreConsumo.h"
#include "sensoreGas.h"
#include "sensorePneumatico.h"
#include "sensoreMotore.h"

namespace sensore{
    class SensorPanel: public QWidget{
        Q_OBJECT
        private:
            Info* info;

        public:
            SensorPanel(Sensore* sensore = nullptr, QWidget* parent = 0);

        signals:
            void StartModify(sensore::Sensore *s);
            void StartSimulation();
            void StartElimination(sensore::Sensore *s);

    };
}
#endif // SENSORPANEL_H
