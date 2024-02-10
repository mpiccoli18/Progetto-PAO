#include "SensorModifyVisitor.h"
#include <QLabel>
#include <QString>
#include <QLineEdit>

#include "sensorePneumatico.h"
#include "sensoreConsumo.h"
#include "sensoreMotore.h"
#include "sensoreBatteria.h"
#include "sensoreGas.h"


namespace sensore{

QWidget* SensorModifyVisitor::getWidget() {
    return widget;
}

void SensorModifyVisitor::modSPneumatico(SensorePneumatico& sPneumatico){
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

void SensorModifyVisitor::modSConsumo(SensoreConsumo& sConsumo){
    widget = new QLabel("Numero di Ottano:");
    QLineEdit *lineOtt = new QLineEdit();
    int ott = sConsumo.getOttano();
    QString qott = QString::number(ott);
    lineOtt->setText(qott);
    widget = lineOtt;
}

void SensorModifyVisitor::modSMotore(SensoreMotore& sMotore){
    widget = new QLabel("Cavalli:");
    QLineEdit *lineCavalli = new QLineEdit();
    unsigned int cav = sMotore.getCavalli();
    QString qcav = QString::number(cav);
    lineCavalli->setText(qcav);
    widget = lineCavalli;
}

void SensorModifyVisitor::modSBatteria(SensoreBatteria& sBatteria){
    widget = new QLabel("Materiali:");
    QLineEdit *lineMat = new QLineEdit();
    std::string mat = sBatteria.getMaterials();
    QString qmat = QString::fromStdString(mat);
    lineMat->setText(qmat);
    widget = lineMat;
}

void SensorModifyVisitor::modSGas(SensoreGas& sGas){
    widget = new QLabel("Impronta:");
    QLineEdit *lineFootp = new QLineEdit();
    double fp = sGas.getFootprint();
    QString qfp = QString::number(fp);
    lineFootp->setText(qfp);
    widget = lineFootp;
}

}
