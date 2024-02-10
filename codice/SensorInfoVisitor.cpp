#include "SensorInfoVisitor.h"
#include <QLabel>
#include <QString>
#include<QLineEdit> //aggiunto per test

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

void SensorInfoVisitor::modSPneumatico(SensorePneumatico& sPneumatico){
    widget = new QLabel("Marca:");
    QLineEdit *lineBrand = new QLineEdit();
    std::string brand = sPneumatico.getBrand();
    QString qbrand = QString::fromStdString(brand);
    lineBrand->setText(qbrand);
    widget = lineBrand;

    widget = new QLabel("Tempo di vita:");
    QLineEdit *lineAge = new QLineEdit();
    double age = sPneumatico.getAge();
    QString qage = QString::number(age);
    lineAge->setText(qage);
    widget = lineAge;
}

void SensorInfoVisitor::modSConsumo(SensoreConsumo& sConsumo){
    widget = new QLabel("Numero di Ottano:");
    QLineEdit *lineOtt = new QLineEdit();
    int ott = sConsumo.getOttano();
    QString qott = QString::number(ott);
    lineOtt->setText(qott);
    widget = lineOtt;
}

void SensorInfoVisitor::modSMotore(SensoreMotore& sMotore){
    widget = new QLabel("Cavalli:");
    QLineEdit *lineCavalli = new QLineEdit();
    unsigned int cav = sMotore.getCavalli();
    QString qcav = QString::number(cav);
    lineCavalli->setText(qcav);
    widget = lineCavalli;
}

void SensorInfoVisitor::modSBatteria(SensoreBatteria& sBatteria){
    widget = new QLabel("Materiali:");
    QLineEdit *lineMat = new QLineEdit();
    std::string mat = sBatteria.getMaterials();
    QString qmat = QString::fromStdString(mat);
    lineMat->setText(qmat);
    widget = lineMat;
}

void SensorInfoVisitor::modSGas(SensoreGas& sGas){
    widget = new QLabel("Impronta:");
    QLineEdit *lineFootp = new QLineEdit();
    double fp = sGas.getFootprint();
    QString qfp = QString::number(fp);
    lineFootp->setText(qfp);
    widget = lineFootp;
}

}
