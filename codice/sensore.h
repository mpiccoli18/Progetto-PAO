#ifndef SENSORE_H
#define SENSORE_H

#include <string>
#include <vector>
#include <QLineEdit>
#include <QJsonObject>
#include "SensorVisitorInterface.h"

namespace sensore{

    class Sensore
    {
        private:
            std::string nome;
            std::string tipo;
            std::string descrizione;
            std::vector<double> valori;
            double min;
            double max;

        public:

            Sensore(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax
            );
            virtual ~Sensore() = default;

            const std::string& getNome() const;
            const std::string& getTipo() const;
            const std::string& getDescrizione() const;
            std::vector<double> getValori() const;
            double getMin() const;
            double getMax() const;

            void setNome(std::string n);
            void setTipo(std::string t);
            void setDescrizione(std::string d);
            void setMin(double vMin);
            void setMax(double vMax);
            void setValori(std::vector<double> v);

            virtual void accept(SensorVisitorInterface& visitor) = 0;
            virtual void acceptSave(SensorVisitorInterface& visitor, QJsonObject* ob) = 0;
    };
}

#endif // SENSORE_H
