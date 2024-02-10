#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H

namespace sensore{

    class SensoreConsumo;
    class SensorePneumatico;
    class SensoreMotore;
    class SensoreBatteria;
    class SensoreGas;
    class Sensore;//aggiunto
    class SensorVisitorInterface{

        public:
            virtual ~SensorVisitorInterface() = default;
            virtual void visitSPneumatico(SensorePneumatico& sPneumatico) = 0;
            virtual void visitSConsumo(SensoreConsumo& sConsumo) = 0;
            virtual void visitSMotore(SensoreMotore& sMotore) = 0;
            virtual void visitSBatteria(SensoreBatteria& sBatteria) = 0;
            virtual void visitSGas(SensoreGas& sGas) = 0;

            virtual void modSPneumatico(SensorePneumatico& sPneumatico) = 0;
            virtual void modSConsumo(SensoreConsumo& sConsumo) = 0;
            virtual void modSMotore(SensoreMotore& sMotore) = 0;
            virtual void modSBatteria(SensoreBatteria& sBatteria) = 0;
            virtual void modSGas(SensoreGas& sGas) = 0;
    };
}
#endif // SENSORVISITORINTERFACE_H
