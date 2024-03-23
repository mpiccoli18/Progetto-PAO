#ifndef SENSORPANEL_H
#define SENSORPANEL_H

#include "Info.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace sensore{
    class SensorPanel: public QWidget{
        Q_OBJECT
        private:
            Info* info;

        public:
            SensorPanel(Sensore* sensore = nullptr, QWidget* parent = 0);

        signals:
            void SegnaleModifica(sensore::Sensore *s);
            void SegnaleSimula();
            void SegnaleElimina(sensore::Sensore *s);

    };
}
#endif // SENSORPANEL_H
