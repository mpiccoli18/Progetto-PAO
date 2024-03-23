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

            virtual void accetta(SensorVisitorInterface& visitor);
            virtual void accettaMod(SensorVisitorInterface& visitor);
            virtual void accettaSalva(SensorVisitorInterface& visitor, QJsonObject* ob);

       };
}
#endif // SENSORECONSUMO_H
