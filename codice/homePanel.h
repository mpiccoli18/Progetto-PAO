#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include <QWidget>
#include <QtCharts>
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
            std::vector<sensore::Sensore*> InsiemeSensori;
        public:
            homePanel(QWidget* parent = 0);

        public slots:
            void Modify(Sensore *s);
            void Simulation();
            void Elimination(Sensore* s);
            void Update(Sensore *s, QLineEdit * nome, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * Max);
            void Save();
            void Open();
            void Close();
            void Exit();
            void View(Sensore* sensore);

        signals:
            void StartSave();
            void StartOpen();
            void StartClose();
            void StartUpdate(Sensore *s, QLineEdit * nome, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * Max);
            void StartExit();

    };
}



#endif // HOMEPANEL_H
