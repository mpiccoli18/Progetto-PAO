#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include <QWidget>
#include<QtCharts>
#include "sensore.h"
#include "sensorPanel.h"

namespace sensore{
    class homePanel : public QWidget{
        Q_OBJECT
        private:
            sensore::Sensore& sensoreGenerale;
            QChartView *chartView;
            QVBoxLayout *modifyView;
            SensorPanel* pannello;
            SensorPanel* barraRicerca;
        public:
            homePanel(sensore::Sensore& s, QWidget* parent = 0);

        public slots:
            void Modify();
            void Simulation();

            void save();
            void open();
            void close();

        signals:
            void StartSave();
            void StartOpen();
            void StartClose();

    };
}



#endif // HOMEPANEL_H
