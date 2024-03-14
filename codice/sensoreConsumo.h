#ifndef SENSORECONSUMO_H
#define SENSORECONSUMO_H

#include "sensore.h"

namespace sensore{
    class SensoreConsumo: public Sensore{
        private:
            unsigned int ottano;
        public:

            SensoreConsumo(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax,
                const unsigned int ot);


            unsigned int getOttano() const;

            void setOttano(unsigned int ot);

            virtual void accept(SensorVisitorInterface& visitor);
            virtual void acceptMod(SensorVisitorInterface& visitor);
            virtual void acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob);

       };
}
#endif // SENSORECONSUMO_H
