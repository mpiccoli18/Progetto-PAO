#include "sensorPanel.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace sensore{
    SensorPanel::SensorPanel(sensore::Sensore& s, QWidget* parent) : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        info = new Info(s);
        info->show();
        layout->addWidget(info);

        QGridLayout* comandi = new QGridLayout();
        layout->addLayout(comandi);

        QPushButton* modify = new QPushButton("Modifica");
        QPushButton* simulation = new QPushButton("Simula");
        comandi->addWidget(modify, 0, 0, 1, 1);
        comandi->addWidget(simulation, 0, 1, 1, 1);
        connect(modify, &QPushButton::pressed, this, &SensorPanel::StartModify);
        connect(simulation, &QPushButton::pressed, this, &SensorPanel::StartSimulation);
    }
}
