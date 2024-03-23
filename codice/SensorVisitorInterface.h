#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H

#include <QJsonObject>
namespace sensore{

    class SensoreConsumo;
    class SensorePneumatico;
    class SensoreMotore;
    class SensoreBatteria;
    class SensoreGas;
    class Sensore;

    class SensorVisitorInterface{
        public:
            virtual ~SensorVisitorInterface() = default;
            virtual void visitaSPneumatico(SensorePneumatico& sPneumatico) = 0;
            virtual void visitaSConsumo(SensoreConsumo& sConsumo) = 0;
            virtual void visitaSMotore(SensoreMotore& sMotore) = 0;
            virtual void visitaSBatteria(SensoreBatteria& sBatteria) = 0;
            virtual void visitaSGas(SensoreGas& sGas) = 0;

            virtual void modSPneumatico(SensorePneumatico* sPneumatico) = 0;
            virtual void modSConsumo(SensoreConsumo* sConsumo) = 0;
            virtual void modSMotore(SensoreMotore* sMotore) = 0;
            virtual void modSBatteria(SensoreBatteria* sBatteria) = 0;
            virtual void modSGas(SensoreGas* sGas) = 0;

            virtual void salvaSPneumatico(SensorePneumatico& sPneumatico, QJsonObject* ob) = 0;
            virtual void salvaSConsumo(SensoreConsumo& sConsumo,QJsonObject* ob) = 0;
            virtual void salvaSMotore(SensoreMotore& sMotore,QJsonObject* ob) = 0;
            virtual void salvaSBatteria(SensoreBatteria& sBatteria,QJsonObject* ob) = 0;
            virtual void salvaSGas(SensoreGas& sGas,QJsonObject* ob) = 0;
    };
}
#endif // SENSORVISITORINTERFACE_H
