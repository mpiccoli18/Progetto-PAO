#ifndef SENSOREMOTORE_H
#define SENSOREMOTORE_H

#include "sensore.h"


namespace sensore{
class SensoreMotore: public Sensore{
private:
    unsigned int horses;
public:

    SensoreMotore(
        const std::string n,
        const std::string t,
        const std::string d,
        const std::vector<double> v,
        const double vMin,
        const double vMax,
        const unsigned int hor);

    unsigned int getHorses() const;

    void setHorses(unsigned int hor);

    virtual void accept(SensorVisitorInterface& visitor);
};
}

#endif // SENSOREMOTORE_H
