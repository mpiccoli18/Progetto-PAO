#ifndef SENSOREBATTERIA_H
#define SENSOREBATTERIA_H

#include "sensore.h"

namespace sensore{
    class SensoreBatteria: public Sensore
    {
        private:
            std::string materiale;
        public:

            SensoreBatteria(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax,
                const std::string mat);

            const std::string getMateriale() const;

            void setMateriale(std::string mat);

            virtual void accept(SensorVisitorInterface& visitor);
            virtual void acceptMod(SensorVisitorInterface& visitor);
            virtual void acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob);

    };
}

#endif // SENSOREBATTERIA_H
