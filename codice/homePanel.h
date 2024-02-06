#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include <QWidget>
#include "sensore.h"
#include "sensorPanel.h"

namespace sensore{
    class homePanel : public QWidget{
        Q_OBJECT
        private:
            sensore::Sensore& sensoreGenerale;
            SensorPanel* pannello;
        public:
            homePanel(sensore::Sensore& s, QWidget* parent = 0);

        public slots:
            void Modify();
            void Simulation();
    };
}



#endif // HOMEPANEL_H
