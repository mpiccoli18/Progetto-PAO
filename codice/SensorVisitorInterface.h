#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H
#include <QLineEdit>
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
            virtual void visitSPneumatico(SensorePneumatico& sPneumatico) = 0;
            virtual void visitSConsumo(SensoreConsumo& sConsumo) = 0;
            virtual void visitSMotore(SensoreMotore& sMotore) = 0;
            virtual void visitSBatteria(SensoreBatteria& sBatteria) = 0;
            virtual void visitSGas(SensoreGas& sGas) = 0;

            virtual std::vector<QLineEdit*> modSPneumatico(SensorePneumatico& sPneumatico) = 0;
            virtual std::vector<QLineEdit*> modSConsumo(SensoreConsumo& sConsumo) = 0;
            virtual std::vector<QLineEdit*> modSMotore(SensoreMotore& sMotore) = 0;
            virtual std::vector<QLineEdit*> modSBatteria(SensoreBatteria& sBatteria) = 0;
            virtual std::vector<QLineEdit*> modSGas(SensoreGas& sGas) = 0;

            virtual void saveSPneumatico(SensorePneumatico& sPneumatico, QJsonObject* ob) = 0;
            virtual void saveSConsumo(SensoreConsumo& sConsumo,QJsonObject* ob) = 0;
            virtual void saveSMotore(SensoreMotore& sMotore,QJsonObject* ob) = 0;
            virtual void saveSBatteria(SensoreBatteria& sBatteria,QJsonObject* ob) = 0;
            virtual void saveSGas(SensoreGas& sGas,QJsonObject* ob) = 0;
    };
}
#endif // SENSORVISITORINTERFACE_H
