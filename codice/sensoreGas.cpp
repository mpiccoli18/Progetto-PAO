#include "sensoreGas.h"

namespace sensore{
    SensoreGas::SensoreGas(const std::string n, const std::string t, const std::string d,
                                     const std::vector<double> v, const double vMin, const double vMax,
                                     const double footp): Sensore(n, t, d, v, vMin, vMax), impronta(footp) {}

    double SensoreGas::getImpronta() const {return impronta;}

    void SensoreGas::setImpronta(double footp) { impronta = footp;}

    void SensoreGas::accept(SensorVisitorInterface& visitor){
        visitor.visitSGas(*this);
    }

    void SensoreGas::acceptMod(SensorVisitorInterface& visitor){
        visitor.modSGas(this);
    }

    void SensoreGas::acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.saveSGas(*this, ob);
    }
}
