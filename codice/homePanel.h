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
            QHBoxLayout *layoutApp;
            QChartView *chartView;
            QWidget *modifyView;
            SensorPanel* pannello;
            searchBarPanel* barraRicerca;
        public:
            homePanel(std::vector<Sensore*> v,Sensore* s, QWidget* parent = 0);

        public slots:
            void Modify();
            void Simulation();
            void Elimination();
            void Update();
            void Save();
            void Open();
            void Close();

            void Exit();

            void View(Sensore* sensore);

        signals:
            void StartSave();
            void StartOpen();
            void StartClose();
            void StartUpdate();
            void StartExit();

    };
}



#endif // HOMEPANEL_H
