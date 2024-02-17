#include <string>
#include <vector>

#include "sensoreConsumo.h"

namespace sensore{
    SensoreConsumo::SensoreConsumo(const std::string n, const std::string t, const std::string d,
                                         const std::vector<double> v, const double vMin, const double vMax,
                                         const int ot): Sensore(n, t, d, v, vMin, vMax), ottano(ot) {}

    int SensoreConsumo::getOttano() const {return ottano;}

    void SensoreConsumo::setOttano(int ot) { ottano = ot;}

    void SensoreConsumo::accept(SensorVisitorInterface& visitor){
        visitor.visitSConsumo(*this);
    }
    void SensoreConsumo::acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.saveSConsumo(*this, ob);
    }
}
