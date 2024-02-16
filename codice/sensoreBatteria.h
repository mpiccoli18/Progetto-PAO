#ifndef SENSOREBATTERIA_H
#define SENSOREBATTERIA_H

#include "sensore.h"

namespace sensore{
    class SensoreBatteria: public Sensore
    {
        private:
            std::string materials;
        public:

            SensoreBatteria(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax,
                const std::string mat);

            const std::string getMaterials() const;

            void setMaterials(std::string mat);

            virtual void accept(SensorVisitorInterface& visitor);
            virtual void acceptModify(SensorVisitorInterface& visitor);
    };
}

#endif // SENSOREBATTERIA_H
