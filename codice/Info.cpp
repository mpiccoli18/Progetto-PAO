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

    name_label = new QLabel();
    layout->addWidget(name_label);

    type_label = new QLabel();
    layout->addWidget(type_label);

    description_label = new QLabel();
    layout->addWidget(description_label);

    valueMin_label = new QLabel();
    layout->addWidget(valueMin_label);

    valueMax_label = new QLabel();
    layout->addWidget(valueMax_label);


    SensorInfoVisitor visitor;
    sensor.accept(visitor);
    layout->addWidget(visitor.getWidget());
}

void Info::show() {
    name_label->setText(QString::fromStdString(sensore.getName()));
    type_label->setText("Tipo: " + QString::fromStdString(sensore.getType()));
    description_label->setText("Descrizione: " + QString::fromStdString(sensore.getDescription()));
    valueMin_label->setText("Val. minimo: " + QString::number(sensore.getValueMin()));
    valueMax_label->setText("Val. massimo: " + QString::number(sensore.getValueMax()));

}

void Info::notify(Sensore& sensor, SensorInfoVisitor& visitor) {
    name_label->setText(QString::fromStdString(sensore.getName()));
    type_label->setText("Tipo: " + QString::fromStdString(sensore.getType()));
    description_label->setText("Descrizione: " + QString::fromStdString(sensore.getDescription()));
    valueMin_label->setText("Val. minimo: " + QString::number(sensore.getValueMin()));
    valueMax_label->setText("Val. massimo: " + QString::number(sensore.getValueMax()));

    sensor.accept(visitor);
}

}
