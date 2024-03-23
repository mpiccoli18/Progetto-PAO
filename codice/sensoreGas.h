#ifndef SENSOREGAS_H
#define SENSOREGAS_H

#include "sensore.h"

namespace sensore{
    class SensoreGas: public Sensore{
    private:
        double impronta;
    public:

        SensoreGas(
            const std::string n,
            const std::string t,
            const std::string d,
            const std::vector<double> v,
            const double vMin,
            const double vMax,
            const double footp);


        double getImpronta() const;

        void setImpronta(double foot);

        virtual void accetta(SensorVisitorInterface& visitor);
        virtual void accettaMod(SensorVisitorInterface& visitor);
        virtual void accettaSalva(SensorVisitorInterface& visitor, QJsonObject* ob);

    };
}

#endif // SENSOREGAS_H
