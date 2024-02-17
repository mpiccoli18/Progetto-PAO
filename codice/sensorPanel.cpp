#include "sensorPanel.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace sensore{
    SensorPanel::SensorPanel(sensore::Sensore* s, QWidget* parent) : QWidget(parent), info(nullptr)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        if (s) {
            QHBoxLayout* infoSensor = new QHBoxLayout();
            info = new Info(*s);
            info->show();
            layout->addLayout(infoSensor);
            infoSensor->addWidget(info);
            QGridLayout* comandi = new QGridLayout();
            infoSensor->addLayout(comandi,Qt::AlignRight);

            QPushButton* modify = new QPushButton("Modifica");
            comandi->addWidget(modify, 0, 0, 1, 1);
            connect(modify, &QPushButton::pressed, this, [this, s]{ emit StartModify(s);});

            QPushButton* simulation = new QPushButton("Simula");
            comandi->addWidget(simulation, 0, 1, 1, 1);
            connect(simulation, &QPushButton::pressed, this, &SensorPanel::StartSimulation);

            QPushButton* elimination = new QPushButton("Elimina");
            comandi->addWidget(elimination, 0, 2, 1, 1);
            connect(elimination, &QPushButton::pressed, this, [this, s]() { emit StartElimination(s); });
            QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            comandi->addItem(spacer, 0, 4, 1, 1);
        }
    }

    void SensorPanel::updateSensor(Sensore* s) {
        if (info) {
            layout()->removeWidget(info); // Rimuovi il widget dal layout
            delete info; // Elimina il widget
            info = nullptr;
        }

        if (s) {
            info = new Info(*s);
            info->show();
            layout()->addWidget(info); // Aggiungi il nuovo widget al layout
        }
    }
}

