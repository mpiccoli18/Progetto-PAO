#include <string>
#include <vector>

#include "sensoreBatteria.h"

namespace sensore{
    SensoreBatteria::SensoreBatteria(const std::string n, const std::string t, const std::string d,
                                 const std::vector<double> v, const double vMin, const double vMax,
                                     const std::string mat): Sensore(n, t, d, v, vMin, vMax), materials(mat) {}

    const std::string SensoreBatteria::getMaterials() const {return materials;}

    void SensoreBatteria::setMaterials(std::string mat) { materials = mat;}

    void SensoreBatteria::accept(SensorVisitorInterface& visitor){
        visitor.visitSBatteria(*this);
    }
    void SensoreBatteria::acceptModify(SensorVisitorInterface& visitor){
        visitor.modSBatteria(*this);
    }

}
