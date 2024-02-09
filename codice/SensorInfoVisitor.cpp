#include "SensorInfoVisitor.h"
#include <QLabel>
#include <QString>

#include "sensorePneumatico.h"
#include "sensoreConsumo.h"
#include "sensoreMotore.h"
#include "sensoreBatteria.h"
#include "sensoreGas.h"


namespace sensore{

QWidget* SensorInfoVisitor::getWidget() {
    return widget;
}

void SensorInfoVisitor::visitSPneumatico(SensorePneumatico& sPneumatico) {
    widget = new QLabel("Marca Pneumatico: " +  QString::fromStdString(sPneumatico.getBrand()));
    widget = new QLabel("Tempo di vita: " +  QString::number(sPneumatico.getAge()));
}

void SensorInfoVisitor::visitSConsumo(SensoreConsumo& sConsumo) {
    widget = new QLabel("Numero di Ottano: " +  QString::number(sConsumo.getOttano()));
}

void SensorInfoVisitor::visitSMotore(SensoreMotore& sMotore) {
    widget = new QLabel("Numero di cavalli: " +  QString::number(sMotore.getCavalli()));
}

void SensorInfoVisitor::visitSBatteria(SensoreBatteria& sBatteria) {
    widget = new QLabel("Materiali: " +  QString::fromStdString(sBatteria.getMaterials()));
}

void SensorInfoVisitor::visitSGas(SensoreGas& sGas) {
    widget = new QLabel("Impronta: " +  QString::number(sGas.getFootprint()));
}

}
