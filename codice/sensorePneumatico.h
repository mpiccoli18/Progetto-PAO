#ifndef SENSOREPNEUMATICO_H
#define SENSOREPNEUMATICO_H

#include "sensore.h"


namespace sensore{
    class SensorePneumatico: public Sensore{
        private:
            std::string brand;
            double age;
        public:

            SensorePneumatico(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax,
                const std::string br,
                const double a);


            const std::string& getBrand() const;
            double getAge() const;

            void setBrand(std::string br);
            void setAge(double a);

            virtual void accept(SensorVisitorInterface& visitor);
    };
}
#endif // SENSOREPNEUMATICO_H
