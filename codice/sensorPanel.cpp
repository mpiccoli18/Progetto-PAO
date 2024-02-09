#include "sensorPanel.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace sensore{
    SensorPanel::SensorPanel(sensore::Sensore& s, QWidget* parent) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignRight | Qt::AlignTop);
        QHBoxLayout* infoSensor = new QHBoxLayout();

        info = new Info(s);
        info->show();
        infoSensor->addWidget(info, Qt::AlignLeft);
        QGridLayout* comandi = new QGridLayout();
        QPushButton* modify = new QPushButton("Modifica");
        QPushButton* simulation = new QPushButton("Simula");
        comandi->addWidget(modify, 0, 0, 1, 1);
        comandi->addWidget(simulation, 0, 1, 1, 1);
        infoSensor->addLayout(comandi, Qt::AlignRight);
        layout->addLayout(infoSensor);
        connect(modify, &QPushButton::pressed, this, &SensorPanel::StartModify);
        connect(simulation, &QPushButton::pressed, this, &SensorPanel::StartSimulation);
    }
}
