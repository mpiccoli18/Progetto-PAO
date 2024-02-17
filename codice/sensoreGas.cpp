#include <string>
#include <vector>

#include "sensoreGas.h"

namespace sensore{
    SensoreGas::SensoreGas(const std::string n, const std::string t, const std::string d,
                                     const std::vector<double> v, const double vMin, const double vMax,
                                     const double footp): Sensore(n, t, d, v, vMin, vMax), footprint(footp) {}

    double SensoreGas::getFootprint() const {return footprint;}

    void SensoreGas::setFootprint(double footp) { footprint = footp;}

    void SensoreGas::accept(SensorVisitorInterface& visitor){
        visitor.visitSGas(*this);
    }
    void SensoreGas::acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.saveSGas(*this, ob);
    }
}
