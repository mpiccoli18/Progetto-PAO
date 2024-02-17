#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include "SensorInfoVisitor.h"
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
        QLabel *labelMarca = new QLabel("Marca Pneumatico: " + QString::fromStdString(sPneumatico.getBrand()));
        QLabel *labelAge = new QLabel("Tempo di vita: " + QString::number(sPneumatico.getAge()));

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(labelMarca);
        layout->addWidget(labelAge);

        QWidget *widgetContainer = new QWidget();
        widgetContainer->setLayout(layout);

        widget = widgetContainer;
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


    void SensorInfoVisitor::saveSPneumatico(SensorePneumatico& sPneumatico, QJsonObject* ob){
        (*ob)["brand"] = QString::fromStdString(sPneumatico.getBrand());
        (*ob)["age"] = QString::number(sPneumatico.getAge());
    }
    void SensorInfoVisitor::saveSConsumo(SensoreConsumo& sConsumo,QJsonObject* ob){
        (*ob)["ottano"] = QString::number(sConsumo.getOttano());
    }
    void SensorInfoVisitor::saveSMotore(SensoreMotore& sMotore,QJsonObject* ob){
        (*ob)["cavalli"] = QString::number(sMotore.getCavalli());
    }
    void SensorInfoVisitor::saveSBatteria(SensoreBatteria& sBatteria,QJsonObject* ob){
        (*ob)["materiali"] = QString::fromStdString(sBatteria.getMaterials());
    }
    void SensorInfoVisitor::saveSGas(SensoreGas& sGas,QJsonObject* ob){
        (*ob)["footprint"] = QString::number(sGas.getFootprint());
    }

}
