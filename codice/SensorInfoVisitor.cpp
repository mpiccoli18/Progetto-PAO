#include "SensorInfoVisitor.h"
#include <QLabel>
#include <QString>
#include<QVBoxLayout>
#include<QLineEdit> //aggiunto per test
#include<iostream>

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

void SensorInfoVisitor::modSPneumatico(SensorePneumatico& sPneumatico){
    // Creazione di un QLabel per la marca
    QLabel *labelMarca = new QLabel("Marca:");
    // Creazione di un QLineEdit per visualizzare la marca
    QLineEdit *lineBrand = new QLineEdit();

    // Ottieni la marca utilizzando la funzione getBrand()
    std::string brand = sPneumatico.getBrand();

    // Converti la marca in una QString
    QString qbrand = QString::fromStdString(brand);

    // Imposta il testo nel QLineEdit con la marca
    lineBrand->setText(qbrand);

    // Creazione di un QLabel per il tempo di vita
    QLabel *labelAge = new QLabel("Tempo di vita:");
    // Creazione di un QLineEdit per visualizzare il tempo di vita
    QLineEdit *lineAge = new QLineEdit();

    // Ottieni il tempo di vita utilizzando la funzione getAge()
    double age = sPneumatico.getAge();

    // Converti il tempo di vita in una QString
    QString qage = QString::number(age);

    // Imposta il testo nel QLineEdit con il tempo di vita
    lineAge->setText(qage);

    // Creazione di un layout per organizzare i widget
    QVBoxLayout *modLayout = new QVBoxLayout();
    modLayout->addWidget(labelMarca);
    modLayout->addWidget(lineBrand);
    modLayout->addWidget(labelAge);
    modLayout->addWidget(lineAge);

    // Creazione di un QWidget per contenere il layout
    QWidget *widgetContainer = new QWidget();
    widgetContainer->setLayout(modLayout);

    // Imposta le dimensioni fisse per il QLineEdit
    int fieldWidth = widgetContainer->width() / 2; // Larghezza della metà del widget padre
    lineBrand->setFixedWidth(fieldWidth);
    lineAge->setFixedWidth(fieldWidth);

    // Assegnazione del widgetContainer a widget
    widget = widgetContainer;
}

void SensorInfoVisitor::modSConsumo(SensoreConsumo& sConsumo){
    // Creazione di un QLabel per il numero di ottano
    QLabel *labelOttano = new QLabel("Numero di Ottano:");
    // Creazione di un QLineEdit per visualizzare il numero di ottano
    QLineEdit *lineOtt = new QLineEdit();

    // Ottenere il numero di ottano utilizzando la funzione getOttano()
    int ott = sConsumo.getOttano();

    // Converti il numero di ottano in una QString
    QString qott = QString::number(ott);

    // Imposta il testo nel QLineEdit con il numero di ottano
    lineOtt->setText(qott);

    // Creazione di un layout per organizzare i widget
    QVBoxLayout *modLayout = new QVBoxLayout();
    modLayout->addWidget(labelOttano);
    modLayout->addWidget(lineOtt);

    // Creazione di un QWidget per contenere il layout
    QWidget *widgetContainer = new QWidget();
    widgetContainer->setLayout(modLayout);

    // Imposta le dimensioni fisse per il QLineEdit
    int fieldWidth = widgetContainer->width() / 2; // Larghezza della metà del widget padre
    lineOtt->setFixedWidth(fieldWidth);

    // Assegnazione del widgetContainer a widget
    widget = widgetContainer;
}

void SensorInfoVisitor::modSMotore(SensoreMotore& sMotore){
    // Creazione di un QLabel per i cavalli
    QLabel *labelCavalli = new QLabel("Cavalli:");
    // Creazione di un QLineEdit per visualizzare il numero di cavalli
    QLineEdit *lineCavalli = new QLineEdit();

    // Ottenere il numero di cavalli utilizzando la funzione getCavalli()
    unsigned int cav = sMotore.getCavalli();

    // Converti il numero di cavalli in una QString
    QString qcav = QString::number(cav);

    // Imposta il testo nel QLineEdit con il numero di cavalli
    lineCavalli->setText(qcav);

    // Creazione di un layout per organizzare i widget
    QVBoxLayout *modLayout = new QVBoxLayout();
    modLayout->addWidget(labelCavalli);
    modLayout->addWidget(lineCavalli);

    // Creazione di un QWidget per contenere il layout
    QWidget *widgetContainer = new QWidget();
    widgetContainer->setLayout(modLayout);

    // Imposta le dimensioni fisse per il QLineEdit
    int fieldWidth = widgetContainer->width() / 2; // Larghezza della metà del widget padre
    lineCavalli->setFixedWidth(fieldWidth);

    // Assegnazione del widgetContainer a widget
    widget = widgetContainer;
}

void SensorInfoVisitor::modSBatteria(SensoreBatteria& sBatteria){
    QLabel *label = new QLabel("Materiali:");
    QLineEdit* lineMat = new QLineEdit();
    std::string mat = sBatteria.getMaterials();

    // Converti le std::string in QString
    QString qmat = QString::fromStdString(mat);

    // Imposta il testo nei campi di input
    lineMat->setText(qmat);

    // Creazione di un layout per organizzare i widget
    QVBoxLayout *modLayout = new QVBoxLayout();
    modLayout->addWidget(label);
    modLayout->addWidget(lineMat);

    // Creazione di un QWidget per contenere il layout
    QWidget *widgetContainer = new QWidget();
    widgetContainer->setLayout(modLayout);

    // Imposta le dimensioni dei campi di input
    int fieldWidth = widgetContainer->width() / 2;
    lineMat->setFixedWidth(fieldWidth);

    // Assegnazione del widgetContainer a widget
    widget = widgetContainer;
}

void SensorInfoVisitor::modSGas(SensoreGas& sGas){
    QLabel *label = new QLabel("Impronta:");
    QLineEdit *lineFootp = new QLineEdit();
    double fp = sGas.getFootprint();
    QString qfp = QString::number(fp);
    lineFootp->setText(qfp);

    // Creazione di un layout per organizzare i widget
    QVBoxLayout *modLayout = new QVBoxLayout();
    modLayout->addWidget(label);
    modLayout->addWidget(lineFootp);

    // Creazione di un QWidget per contenere il layout
    QWidget *widgetContainer = new QWidget();
    widgetContainer->setLayout(modLayout);

    // Imposta le dimensioni dei campi di input
    int fieldWidth = widgetContainer->width() / 2;
    lineFootp->setFixedWidth(fieldWidth);

    // Assegnazione del widgetContainer a widget
    widget = widgetContainer;
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
