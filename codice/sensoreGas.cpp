#include "sensoreGas.h"

namespace sensore{
    SensoreGas::SensoreGas(const std::string n, const std::string t, const std::string d,
                                     const std::vector<double> v, const double vMin, const double vMax,
                                     const double footp): Sensore(n, t, d, v, vMin, vMax), impronta(footp) {}

    double SensoreGas::getImpronta() const {return impronta;}

    void SensoreGas::setImpronta(double footp) { impronta = footp;}

    void SensoreGas::accetta(SensorVisitorInterface& visitor){
        visitor.visitaSGas(*this);
    }

    void SensoreGas::accettaMod(SensorVisitorInterface& visitor){
        visitor.modSGas(this);
    }

    void SensoreGas::accettaSalva(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.salvaSGas(*this, ob);
    }
}
