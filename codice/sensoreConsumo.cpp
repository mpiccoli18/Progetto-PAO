#include "sensoreConsumo.h"

namespace sensore{
    SensoreConsumo::SensoreConsumo(const std::string n, const std::string t, const std::string d,
                                   const std::vector<double> v, const double vMin, const double vMax,
                                   const unsigned int ot): Sensore(n, t, d, v, vMin, vMax), ottano(ot) {}

    unsigned int SensoreConsumo::getOttano() const {return ottano;}

    void SensoreConsumo::setOttano(unsigned int ot) { ottano = ot;}

    void SensoreConsumo::accetta(SensorVisitorInterface& visitor){
        visitor.visitaSConsumo(*this);
    }

    void SensoreConsumo::accettaMod(SensorVisitorInterface& visitor){
        visitor.modSConsumo(this);
    }

    void SensoreConsumo::accettaSalva(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.salvaSConsumo(*this, ob);
    }
}
