#include "sensorPanel.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace sensore{
    SensorPanel::SensorPanel(sensore::Sensore& s, QWidget* parent) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QHBoxLayout* infoSensor = new QHBoxLayout();
        layout->addLayout(infoSensor);

        info = new Info(s);
        info->show();
        infoSensor->addWidget(info);

        QGridLayout* comandi = new QGridLayout();
        infoSensor->addLayout(comandi,Qt::AlignRight);

        QPushButton* modify = new QPushButton("Modifica");
        comandi->addWidget(modify, 0, 0, 1, 1);
        connect(modify, &QPushButton::pressed, this, &SensorPanel::StartModify);

        QPushButton* simulation = new QPushButton("Simula");
        comandi->addWidget(simulation, 0, 1, 1, 1);
        connect(simulation, &QPushButton::pressed, this, &SensorPanel::StartSimulation);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        comandi->addItem(spacer, 0, 4, 1, 1);
    }
}
