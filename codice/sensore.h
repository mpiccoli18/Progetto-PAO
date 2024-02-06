#ifndef SENSORE_H
#define SENSORE_H

#include <string>
#include <vector>

#include "SensorVisitorInterface.h"

namespace sensore{

    class Sensore
    {
        private:

            std::string name;
            std::string type;
            std::string description;
            std::vector<double> values;
            static const unsigned int maxMesi;
            double valueMin;
            double valueMax;

        public:

            Sensore(
                const std::string n,
                const std::string t,
                const std::string d,
                const std::vector<double> v,
                const double vMin,
                const double vMax
            );
            virtual ~Sensore();

            const std::string& getName() const;
            const std::string& getType() const;
            const std::string& getDescription() const;
            std::vector<double> getValues() const;
            unsigned int getMaxMesi() const;
            double getValueMin() const;
            double getValueMax() const;

            void setName(std::string n);
            void setType(std::string t);
            void setDescription(std::string d);
            void setValueMin(double vMin);
            void setValueMax(double vMax);
            void setValues(std::vector<double> v);

            virtual void accept(SensorVisitorInterface& visitor) = 0;

            double StartSimulation();

    };
}

#endif // SENSORE_H
