#include "sensoreBatteria.h"

namespace sensore{
    SensoreBatteria::SensoreBatteria(const std::string n, const std::string t, const std::string d,
                                 const std::vector<double> v, const double vMin, const double vMax,
                                     const std::string mat): Sensore(n, t, d, v, vMin, vMax), materiale(mat) {}

    const std::string SensoreBatteria::getMateriale() const {return materiale;}

    void SensoreBatteria::setMateriale(std::string mat) { materiale = mat;}

    void SensoreBatteria::accept(SensorVisitorInterface& visitor){
        visitor.visitSBatteria(*this);
    }

    void SensoreBatteria::acceptMod(SensorVisitorInterface& visitor){
        visitor.modSBatteria(*this);
    }

    void SensoreBatteria::acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.saveSBatteria(*this, ob);
    }


}
