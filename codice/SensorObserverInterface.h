#ifndef SENSOR_OBSERVER_INTERFACE_H
#define SENSOR_OBSERVER_INTERFACE_H

namespace sensore{

class Sensor;

class SensorObserverInterface {
  public:
    virtual ~SensorObserverInterface() = default;
    virtual void notify(Sensor& sens) = 0;
};

}

#endif