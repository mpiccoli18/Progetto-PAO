#ifndef INFO_H
#define INFO_H

#include <QWidget>
#include <QLabel>
#include "sensore.h"
#include "SensorInfoVisitor.h"

namespace sensore {

    class Info: public QWidget{
        Q_OBJECT
        private:
            Sensore& sensore;
            QLabel* name_label;
            QLabel* type_label;
            QLabel* description_label;
            QLabel* valueMin_label;
            QLabel* valueMax_label;
        public:
            Info(Sensore& sensore, QWidget* parent = 0);
            void show();
            virtual void notify(Sensore& sensor, SensorInfoVisitor& visitor);
    };
}

#endif // INFO_H
