#ifndef SENSOREMOTORE_H
#define SENSOREMOTORE_H

#include "sensore.h"


namespace sensore{
class SensoreMotore: public Sensore{
private:
    unsigned int cavalli;
public:

    SensoreMotore(
        const std::string n,
        const std::string t,
        const std::string d,
        const std::vector<double> v,
        const double vMin,
        const double vMax,
        const unsigned int hor);

    unsigned int getCavalli() const;

    void setCavalli(unsigned int hor);

    virtual void accept(SensorVisitorInterface& visitor);
    virtual void acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob);

};
}

#endif // SENSOREMOTORE_H
