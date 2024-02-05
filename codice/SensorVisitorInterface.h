#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H

namespace sensore{

    class SensoreConsumo;
    class SensorePneumatico;
    class SensoreMotore;
    class SensoreBatteria;
    class SensoreGas;
    class SensorVisitorInterface{

        public:
            virtual ~SensorVisitorInterface() = default;
            virtual void visitSensorPneumatico(SensorePneumatico& sPneumatico) = 0;
            virtual void visitSensorConsumo(SensoreConsumo& sConsumo) = 0;
            virtual void visitSensorMotore(SensoreMotore& sMotore) = 0;
            virtual void visitSensorBatteria(SensoreBatteria& sBatteria) = 0;
            virtual void visitSensorGas(SensoreGas& sGas) = 0;
    };
}
#endif // SENSORVISITORINTERFACE_H
