#include "sensorePneumatico.h"

namespace sensore{
    SensorePneumatico::SensorePneumatico(const std::string n, const std::string t, const std::string d,
                                     const std::vector<double> v, const double vMin, const double vMax,
                                     const std::string br, const double a): Sensore(n, t, d, v, vMin, vMax), marcaPneu(br), eta(a) {}

    const std::string& SensorePneumatico::getMarcaPneu() const {return marcaPneu;}
    double SensorePneumatico::getEta() const {return eta;}

    void SensorePneumatico::setMarcaPneu(std::string br) { marcaPneu = br;}
    void SensorePneumatico::setEta(double a) { eta = a;}

    void SensorePneumatico::accetta(SensorVisitorInterface& visitor){
        visitor.visitaSPneumatico(*this);
    }

    void SensorePneumatico::accettaMod(SensorVisitorInterface& visitor){
        visitor.modSPneumatico(this);
    }

    void SensorePneumatico::accettaSalva(SensorVisitorInterface& visitor, QJsonObject* ob){
        visitor.salvaSPneumatico(*this, ob);
    }
}
