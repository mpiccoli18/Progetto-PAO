#include <string>
#include <vector>

#include "sensoreMotore.h"

namespace sensore{
SensoreMotore::SensoreMotore(const std::string n, const std::string t, const std::string d,
                               const std::vector<double> v, const double vMin, const double vMax,
                               const unsigned int hor): Sensore(n, t, d, v, vMin, vMax), cavalli(hor) {}

unsigned int SensoreMotore::getCavalli() const {return cavalli;}

void SensoreMotore::setCavalli(unsigned int hor) { cavalli = hor;}

void SensoreMotore::accept(SensorVisitorInterface& visitor){
    visitor.visitSMotore(*this);
}
}
