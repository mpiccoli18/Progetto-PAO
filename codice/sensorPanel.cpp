#include "sensorPanel.h"

namespace sensore{
    SensorPanel::SensorPanel(sensore::Sensore* s, QWidget* parent) : QWidget(parent), info(nullptr)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        if(s) {
            QHBoxLayout* infoSensor = new QHBoxLayout();
            info = new Info(*s);
            info->show();
            layout->addLayout(infoSensor);
            infoSensor->addWidget(info);
            QGridLayout* comandi = new QGridLayout();
            infoSensor->addLayout(comandi,Qt::AlignRight);
            QSpacerItem *spazio = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
            comandi->addItem(spazio, 0, 0, 1, 1);
            QPushButton* modifica = new QPushButton("Modifica");
            modifica->setShortcut(QKeySequence("Ctrl+M"));
            modifica->setObjectName("buttonMod");
            modifica->setStyleSheet("QPushButton#buttonMod {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                "QPushButton#buttonMod:hover{background-color: lightgrey;}");
            modifica->setFixedWidth(100);
            comandi->addWidget(modifica, 0, 2, 1, 1);
            connect(modifica, &QPushButton::pressed, this, [this, s]{ emit StartModify(s);});

            QPushButton* simula = new QPushButton("Simula");
            simula->setShortcut(QKeySequence("Ctrl+I"));
            simula->setObjectName("buttonSimula");
            simula->setStyleSheet("QPushButton#buttonSimula {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                "QPushButton#buttonSimula:hover{background-color: lightgrey;}");
            simula->setFixedWidth(100);
            comandi->addWidget(simula, 0, 3, 1, 1);
            connect(simula, &QPushButton::pressed, this, &SensorPanel::StartSimulation);

            QPushButton* elimina = new QPushButton("Elimina");
            elimina->setObjectName("buttonElimina");
            elimina->setStyleSheet("QPushButton#buttonElimina {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                "QPushButton#buttonElimina:hover{background-color: red;}");
            elimina->setFixedWidth(100);
            comandi->addWidget(elimina, 0, 4, 1, 1);
            connect(elimina, &QPushButton::pressed, this, [this, s]() { emit StartElimination(s); });
        }
    }
}

