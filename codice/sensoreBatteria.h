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

            virtual void accetta(SensorVisitorInterface& visitor);
            virtual void accettaMod(SensorVisitorInterface& visitor);
            virtual void accettaSalva(SensorVisitorInterface& visitor, QJsonObject* ob);

    };
}

#endif // SENSOREBATTERIA_H
