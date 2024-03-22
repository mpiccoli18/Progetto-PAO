#include "Info.h"

namespace sensore {
    Info::Info(Sensore& sensor, QWidget* parent)
        : QWidget(parent), sensore(sensor)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        nome_label = new QLabel();
        layout->addWidget(nome_label);

        tipo_label = new QLabel();
        layout->addWidget(tipo_label);

        descrizione_label = new QLabel();
        layout->addWidget(descrizione_label);

        min_label = new QLabel();
        layout->addWidget(min_label);

        max_label = new QLabel();
        layout->addWidget(max_label);

        SensorInfoVisitor visitor;
        sensor.accept(visitor);
        layout->addWidget(visitor.getWidget());
    }

    void Info::show() {
        nome_label->setText(QString::fromStdString(sensore.getNome()));
        nome_label->setObjectName("nome");
        nome_label->setStyleSheet("QLabel#nome {font: bold 20px;}");
        tipo_label->setText("Tipo: " + QString::fromStdString(sensore.getTipo()));
        tipo_label->setObjectName("tipo");
        tipo_label->setStyleSheet("QLabel#tipo {font: italic 16px;}");
        descrizione_label->setText("Descrizione: " + QString::fromStdString(sensore.getDescrizione()));
        descrizione_label->setObjectName("descrizione");
        descrizione_label->setFixedSize(400, 70);
        descrizione_label->setStyleSheet("QLabel#descrizione {font: italic 16px;}");
        descrizione_label->setWordWrap(true);
        min_label->setText("Val. minimo: " + QString::number(sensore.getMin()));
        min_label->setObjectName("min");
        min_label->setStyleSheet("QLabel#min {font: italic 16px;}");
        max_label->setText("Val. massimo: " + QString::number(sensore.getMax()));
        max_label->setObjectName("max");
        max_label->setStyleSheet("QLabel#max {font: italic 16px;}");
    }
}
