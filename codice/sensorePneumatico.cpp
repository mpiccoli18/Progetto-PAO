#include <string>
#include <vector>

#include "sensorePneumatico.h"

namespace sensore{
    SensorePneumatico::SensorePneumatico(const std::string n, const std::string t, const std::string d,
                                     const std::vector<double> v, const double vMin, const double vMax,
                                     const std::string marca, const double a): Sensore(n, t, d, v, vMin, vMax), marcaPneumatico(marca), anni(a) {}

    const std::string& SensorePneumatico::getMarca() const {return marcaPneumatico;}
    const double& SensorePneumatico::getAnni() const {return anni;}

    void SensorePneumatico::setMarca(std::string m) { marcaPneumatico = m;}
    void SensorePneumatico::setAnni(double a) { anni = a;}

    void SensorePneumatico::accept(SensorVisitorInterface& visitor){
        visitor.visitSensorPneumatico(*this);
    }
}
