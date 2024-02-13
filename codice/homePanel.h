#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include <QWidget>
#include<QtCharts>
#include "sensore.h"
#include "sensorPanel.h"
#include "searchBarPanel.h"

namespace sensore{
    class homePanel : public QWidget{
        Q_OBJECT
        private:
            sensore::Sensore* sensoreGenerale;
            QChartView *chartView = nullptr;
            QWidget* modifyView = nullptr;
            SensorPanel* pannello;
            searchBarPanel* barraRicerca;
        public:
            homePanel(std::vector<Sensore*> v,Sensore* s, QWidget* parent = 0);

        public slots:
            void Modify();
            void Simulation();
            void Elimination();

            void save();
            void open();
            void close();

            void exit();

            void View();

        signals:
            void StartSave();
            void StartOpen();
            void StartClose();

            void StartExit();

    };
}



#endif // HOMEPANEL_H
