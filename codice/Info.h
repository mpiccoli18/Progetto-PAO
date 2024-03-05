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
            QLabel* nome_label;
            QLabel* tipo_label;
            QLabel* descrizione_label;
            QLabel* min_label;
            QLabel* max_label;
        public:
            Info(Sensore& sensore, QWidget* parent = 0);
            void show();
    };
}

#endif // INFO_H
