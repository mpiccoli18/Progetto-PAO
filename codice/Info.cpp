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

    hit_points_label = new QLabel();
    layout->addWidget(hit_points_label);

    strength_label = new QLabel();
    layout->addWidget(strength_label);

    CharacterInfoVisitor visitor;
    character.accept(visitor);
    layout->addWidget(visitor.getWidget());

    character.registerObserver(this);
}

void Info::show() {
    name_label->setText(QString::fromStdString(character.getName()));
    hit_points_label->setText("HP: " + QString::number(character.getHitPoints()) + "/" + QString::number(character.getMaxHitPoints()));
    strength_label->setText("Strength: " + QString::number(character.getStrength()));
}

}
