#ifndef SENSOREPNEUMATICO_H
#define SENSOREPNEUMATICO_H

#include "sensore.h"

namespace sensore{
    class SensorePneumatico: public Sensore{
        private:
            std::string marcaPneu;
            double eta;
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


            const std::string& getMarcaPneu() const;
            double getEta() const;

            void setMarcaPneu(std::string br);
            void setEta(double a);

            virtual void accept(SensorVisitorInterface& visitor);
            virtual void acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob);

    };
}
#endif // SENSOREPNEUMATICO_H
