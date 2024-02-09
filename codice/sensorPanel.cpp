#include "sensorPanel.h"
#include <QHBoxLayout>
#include <QPushButton>

namespace sensore{
    SensorPanel::SensorPanel(sensore::Sensore& s, QWidget* parent) : QWidget(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        QHBoxLayout* sensorc = new QHBoxLayout();
        layout->addLayout(sensorc);

        info = new Info(s);
        info->show();
        sensorc->addWidget(info);

        QGridLayout* comandi = new QGridLayout();
        sensorc->addLayout(comandi,Qt::AlignRight);

        QPushButton* modify = new QPushButton("Modifica");
        QPushButton* simulation = new QPushButton("Simula");
        comandi->addWidget(modify, 0, 0, 1, 1);
        comandi->addWidget(simulation, 0, 1, 1, 1);
        connect(modify, &QPushButton::pressed, this, &SensorPanel::StartModify);
        connect(simulation, &QPushButton::pressed, this, &SensorPanel::StartSimulation);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        comandi->addItem(spacer, 0, 4, 1, 1);
    }
}
