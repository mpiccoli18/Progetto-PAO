#include "Info.h"
#include <QVBoxLayout>
#include <QString>
#include "SensorInfoVisitor.h"

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
        tipo_label->setText("Tipo: " + QString::fromStdString(sensore.getTipo()));
        descrizione_label->setText("Descrizione: " + QString::fromStdString(sensore.getDescrizione()));
        min_label->setText("Val. minimo: " + QString::number(sensore.getMin()));
        max_label->setText("Val. massimo: " + QString::number(sensore.getMax()));
    }
}
