#ifndef SENSORECONSUMO_H
#define SENSORECONSUMO_H

#include "sensore.h"

namespace sensore{
    class SensoreConsumo: public Sensore{
        private:
            std::string tipoCarburante;
        public:

            SensoreConsumo(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax,
                const std::string tCarburante);


            const std::string& getTipoCarburante() const;

            void setTipoCarburante(std::string tCarburante);

            virtual void accept(SensorVisitorInterface& visitor);
       };
}
#endif // SENSORECONSUMO_H
