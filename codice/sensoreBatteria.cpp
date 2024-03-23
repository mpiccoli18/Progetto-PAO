#include "sensoreBatteria.h"

namespace sensore{
    SensoreBatteria::SensoreBatteria(const std::string n, const std::string t, const std::string d,
                                 const std::vector<double> v, const double vMin, const double vMax,
                                     const std::string mat): Sensore(n, t, d, v, vMin, vMax), materiale(mat) {}

    const std::string SensoreBatteria::getMateriale() const {return materiale;}

    void SensoreBatteria::setMateriale(std::string mat) { materiale = mat;}

    void SensoreBatteria::accetta(SensorVisitorInterface& visitor){
        visitor.visitaSBatteria(*this);
    }

    void SensoreBatteria::accettaMod(SensorVisitorInterface& visitor){
        visitor.modSBatteria(this);
    }

    void SensoreBatteria::accettaSalva(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.salvaSBatteria(*this, ob);
    }


}
