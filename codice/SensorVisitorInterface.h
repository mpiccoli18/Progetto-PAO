#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H

namespace sensore{

    class sensoreConsumo;
    class sensorePneumatico;
    class SensorVisitorInterface{

        public:
            virtual ~SensorVisitorInterface() = default;
            virtual void visitSensorPneumatico(sensorePneumatico& sPneumatico) = 0;
            virtual void visitSensorConsumo(sensoreConsumo& sConsumo) = 0;

    };
}
#endif // SENSORVISITORINTERFACE_H
