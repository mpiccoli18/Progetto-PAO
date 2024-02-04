#ifndef SENSOREPNEUMATICO_H
#define SENSOREPNEUMATICO_H

#include "sensore.h"


namespace sensore{
    class SensorePneumatico: public Sensore{
        private:
            std::string marcaPneumatico;
            double anni;
        public:

            SensorePneumatico(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax,
                const std::string marca,
                const double a);


            const std::string& getMarca() const;
            const double& getAnni() const;

            void setMarca(std::string m);
            void setAnni(double a);
    };
}
#endif // SENSOREPNEUMATICO_H
