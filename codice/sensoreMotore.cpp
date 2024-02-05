#include <string>
#include <vector>

#include "sensoreMotore.h"

namespace sensore{
SensoreMotore::SensoreMotore(const std::string n, const std::string t, const std::string d,
                               const std::vector<double> v, const double vMin, const double vMax,
                               const unsigned int hor): Sensore(n, t, d, v, vMin, vMax), horses(hor) {}

unsigned int SensoreMotore::getHorses() const {return horses;}

void SensoreMotore::setHorses(unsigned int hor) { horses = hor;}

void SensoreMotore::accept(SensorVisitorInterface& visitor){
    visitor.visitSensorMotore(*this);
}
}
