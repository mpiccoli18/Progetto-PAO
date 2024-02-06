#include <string>
#include <vector>

#include "sensorePneumatico.h"

namespace sensore{
    SensorePneumatico::SensorePneumatico(const std::string n, const std::string t, const std::string d,
                                     const std::vector<double> v, const double vMin, const double vMax,
                                     const std::string br, const double a): Sensore(n, t, d, v, vMin, vMax), brand(br), age(a) {}

    const std::string& SensorePneumatico::getBrand() const {return brand;}
    double SensorePneumatico::getAge() const {return age;}

    void SensorePneumatico::setBrand(std::string br) { brand = br;}
    void SensorePneumatico::setAge(double a) { age = a;}

    void SensorePneumatico::accept(SensorVisitorInterface& visitor){
        visitor.visitSPneumatico(*this);
    }
}
