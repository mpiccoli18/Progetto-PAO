#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include "sensore.h"
#include "sensorPanel.h"
#include "searchBarPanel.h"
#include <QString>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QtCharts>
#include <QLineEdit>
#include <vector>
#include <QWidget>
#include <QtCharts>

namespace sensore{
    class homePanel : public QWidget{
        Q_OBJECT
        private:
            sensore::Sensore* sensoreGenerale;
            QHBoxLayout *layoutApp;
            QChartView *grafico;
            QWidget *modifica;
            SensorPanel* pannello;
            searchBarPanel* barraRicerca;
            QWidget *creazione;
            modello* mod;
            QString nomeFile;
            QPushButton* saveStessoFile;
            bool modificato = false;
        public:
            homePanel(QWidget* parent = 0);

        public slots:
            void Modify(Sensore *s);
            void Simulation();
            void Elimination(Sensore* s);
            void Open();
            void Save();
            void SaveStessoFile();
            void Create();
            void View(Sensore* sensore);
            void SensorSelected(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor,QVBoxLayout* createLayout);

        signals:
            void StartSave();
            void StartSaveStessoFile();
            void StartOpen();
            void StartCreate();
            void StartSensorSelected(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor,QVBoxLayout* createLayout);

    };
}

#endif // HOMEPANEL_H
