#include <string>
#include <vector>
#include "sensore.h"


namespace sensore{

    Sensore::Sensore(
        const std::string n,
        const std::string t,
        const std::string d,
        const std::vector<double> v,
        const double vMin,
        const double vMax
    ) : name(n), type(t), description(d), values(v), valueMin(vMin), valueMax(vMax) {}

    Sensore::~Sensore(){ delete &values;}
    const std::string& Sensore::getName() const {return name;}
    const std::string& Sensore::getType() const {return type;}
    const std::string& Sensore::getDescription() const {return description;}
    unsigned int Sensore::getMaxMesi() const {return maxMesi;}
    double Sensore::getValueMin() const {return valueMin;}
    double Sensore::getValueMax() const {return valueMax;}

    void Sensore::setName(std::string n) { std::string name = n; }
    void Sensore::setType(std::string t) { std::string type = t; }
    void Sensore::setDescription(std::string d) { std::string description = d; }
    void Sensore::setValueMin(double vMin) { valueMin = vMin; }
    void Sensore::setValueMax(double vMax) { valueMax = vMax; }
    void Sensore::setValues(std::vector<double> v) {
        for(auto i = v.begin(); i != v.end(); i++)
        {
            values.push_back(*i);
        }
    }

    const unsigned int Sensore::maxMesi=12;
}
