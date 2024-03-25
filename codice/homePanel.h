#ifndef HOMEPANEL_H
#define HOMEPANEL_H

#include "sensore.h"
#include "sensorPanel.h"
#include "searchBarPanel.h"
#include <QString>
#include <QChartView>
#include <QVBoxLayout>
#include <QSplineSeries>
#include <QLineEdit>
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
            QPushButton* salvaStessoFile;
            bool modificato;
            QComboBox* sceltaGrafico;
            QPushButton* comandiZoom;
            QLabel* legenda;
            int zoomGrafico;
            QWidget* elimina;

        public:
            homePanel(QWidget* parent = 0);
            void comandiGrafico(QKeyEvent *event);
            void spostamentoAsseX(int direzione);
            void spostamentoAsseY(int direzione);
            void rimozioneZoom();
            void zoomIn();
            void zoomOut();

        public slots:
            void Modifica(sensore::Sensore *s);
            void Simula();
            void Elimina(sensore::Sensore* s);
            void Apri();
            void Salva();
            void SalvaStessoFile();
            void Crea();
            void Mostra(sensore::Sensore* sensore);
            void SensoreSelezionato(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor,QVBoxLayout* createLayout);
            void MostraNascondiLegenda();
        signals:
            void SegnaleSalva();
            void SegnaleSalvaStessoFile();
            void SegnaleApri();
            void SegnaleCrea();
            void SegnaleSensoreSelezionato(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor,QVBoxLayout* createLayout);

    };
}

#endif // HOMEPANEL_H
