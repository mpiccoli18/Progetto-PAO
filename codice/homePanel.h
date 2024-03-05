#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include <QWidget>
#include <QtCharts>
#include "sensore.h"
#include "sensorPanel.h"
#include "searchBarPanel.h"
#include "modello.h"

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
            std::vector<sensore::Sensore*> InsiemeSensori;
        public:
            homePanel(QWidget* parent = 0);
            Sensore* createSensorFromJson(const QString& sensorName, const QJsonObject& sensorObject);
            std::vector<double> parseJsonArray(const QJsonArray& jsonArray);

        public slots:
            void Modify(Sensore *s);
            void Simulation();
            void Elimination(Sensore* s);
            void Update(Sensore *s, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * max);
            void Open();
            void Save();
            void Create();
            void Exit();
            void View(Sensore* sensore);
            void SensorSelected(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor,QVBoxLayout* createLayout);

        signals:
            void StartSave();
            void StartOpen();
            void StartCreate();
            void StartUpdate(Sensore *s, QLineEdit * tipo, QLineEdit *descrizione, QLineEdit * val, QLineEdit * min, QLineEdit * max);
            void StartExit();
            void StartSensorSelected(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor,QVBoxLayout* createLayout);

    };
}

#endif // HOMEPANEL_H
