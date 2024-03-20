#include "SensorInfoVisitor.h"
#include "modello.h"

namespace sensore{
    QWidget* SensorInfoVisitor::getWidget() {
        return widget;
    }

    void SensorInfoVisitor::setModello(modello *m){
        mod = m;
    }

    QPushButton* SensorInfoVisitor::getButton(){
        return confirmButton;
    }

    void SensorInfoVisitor::visitSPneumatico(SensorePneumatico& sPneumatico) {
        widget = new QLabel("Marca Pneumatico: " + QString::fromStdString(sPneumatico.getMarcaPneu()) +
                            "\nTempo di vita: " + QString::number(sPneumatico.getEta()));
        widget->setObjectName("pneumatico");
        widget->setStyleSheet("QLabel#pneumatico {font: italic 16px;}");
    }

    void SensorInfoVisitor::visitSConsumo(SensoreConsumo& sConsumo) {
        widget = new QLabel("Numero di Ottano: " +  QString::number(sConsumo.getOttano()));
        widget->setObjectName("consumo");
        widget->setStyleSheet("QLabel#consumo {font: italic 16px;}");
    }

    void SensorInfoVisitor::visitSMotore(SensoreMotore& sMotore) {
        widget = new QLabel("Numero di cavalli: " +  QString::number(sMotore.getCavalli()));
        widget->setObjectName("motore");
        widget->setStyleSheet("QLabel#motore {font: italic 16px;}");
    }

    void SensorInfoVisitor::visitSBatteria(SensoreBatteria& sBatteria) {
        widget = new QLabel("Materiali: " +  QString::fromStdString(sBatteria.getMateriale()));
        widget->setObjectName("batteria");
        widget->setStyleSheet("QLabel#batteria {font: italic 16px;}");
    }

    void SensorInfoVisitor::visitSGas(SensoreGas& sGas) {
        widget = new QLabel("Impronta: " +  QString::number(sGas.getImpronta()));
        widget->setObjectName("gas");
        widget->setStyleSheet("QLabel#gas {font: italic 16px;}");
    }

    void SensorInfoVisitor::modSPneumatico(SensorePneumatico* sPneumatico){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel* titolo = new QLabel("Modifica delle informazioni di: " + QString::fromStdString(sPneumatico->getNome()));
        titolo->setStyleSheet("font: bold 20px;");
        QLabel *labeltype = new QLabel("Tipologia:");
        labeltype->setStyleSheet("font: italic 14px;");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        labeldescr->setStyleSheet("font: italic 14px;");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        labelmin->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        labelmax->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        labelval->setStyleSheet("font: italic 14px;");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelMarca = new QLabel("Marca:");
        labelMarca->setStyleSheet("font: italic 14px;");
        QLineEdit* lineMarca = new QLineEdit(widget);

        QLabel *labelEta = new QLabel("Tempo di vita:");
        labelEta->setStyleSheet("font: italic 14px;");
        QLineEdit *lineEta = new QLineEdit(widget);

        std::vector<double> v = sPneumatico->getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sPneumatico->getTipo()));
        lineDescr->setText(QString::fromStdString(sPneumatico->getDescrizione()));
        lineMin->setText(QString::number(sPneumatico->getMin()));
        lineMax->setText(QString::number(sPneumatico->getMax()));
        lineVal->setText(qval);
        lineMarca->setText(QString::fromStdString(sPneumatico->getMarcaPneu()));
        lineEta->setText(QString::number(sPneumatico->getEta()));

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineMarca->setFixedWidth(fieldWidth);
        lineEta->setFixedWidth(fieldWidth);

        modLayout->addWidget(titolo, 0, Qt::AlignCenter);
        modLayout->addWidget(labeltype);
        modLayout->addWidget(lineType, 0, Qt::AlignLeft);

        modLayout->addWidget(labeldescr);
        modLayout->addWidget(lineDescr, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmin);
        modLayout->addWidget(lineMin, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmax);
        modLayout->addWidget(lineMax, 0, Qt::AlignLeft);

        modLayout->addWidget(labelval);
        modLayout->addWidget(lineVal, 0, Qt::AlignLeft);

        modLayout->addWidget(labelMarca);
        modLayout->addWidget(lineMarca, 0, Qt::AlignLeft);

        modLayout->addWidget(labelEta);
        modLayout->addWidget(lineEta, 0, Qt::AlignLeft);

        confirmButton = new QPushButton("Conferma", widget);

        QPushButton::connect(confirmButton, &QPushButton::pressed, [this, sPneumatico, lineType, lineDescr, lineVal, lineMin, lineMax, lineMarca, lineEta]() {
            mod->aggiornaSens(sPneumatico, lineType, lineDescr, lineVal, lineMin, lineMax);
            mod->modificaSensorePneumatico(sPneumatico, lineMarca, lineEta);
        });
    }

    void SensorInfoVisitor::modSConsumo(SensoreConsumo* sConsumo){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel* titolo = new QLabel("Modifica delle informazioni di: " + QString::fromStdString(sConsumo->getNome()));
        titolo->setStyleSheet("font: 18px bold;");
        QLabel *labeltype = new QLabel("Tipologia:");
        labeltype->setStyleSheet("font: italic 14px;");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        labeldescr->setStyleSheet("font: italic 14px;");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        labelmin->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        labelmax->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        labelval->setStyleSheet("font: italic 14px;");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelOtt = new QLabel("Numero di ottano:");
        labelOtt->setStyleSheet("font: italic 14px;");
        QLineEdit* lineOtt = new QLineEdit(widget);

        std::vector<double> v = sConsumo->getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sConsumo->getTipo()));
        lineDescr->setText(QString::fromStdString(sConsumo->getDescrizione()));
        lineMin->setText(QString::number(sConsumo->getMin()));
        lineMax->setText(QString::number(sConsumo->getMax()));
        lineVal->setText(qval);
        lineOtt->setText(QString::number(sConsumo->getOttano()));

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineOtt->setFixedWidth(fieldWidth);

        modLayout->addWidget(titolo, 0, Qt::AlignCenter);
        modLayout->addWidget(labeltype);
        modLayout->addWidget(lineType, 0, Qt::AlignLeft);

        modLayout->addWidget(labeldescr);
        modLayout->addWidget(lineDescr, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmin);
        modLayout->addWidget(lineMin, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmax);
        modLayout->addWidget(lineMax, 0, Qt::AlignLeft);

        modLayout->addWidget(labelval);
        modLayout->addWidget(lineVal, 0, Qt::AlignLeft);

        modLayout->addWidget(labelOtt);
        modLayout->addWidget(lineOtt, 0, Qt::AlignLeft);

        confirmButton = new QPushButton("Conferma", widget);

        QPushButton::connect(confirmButton, &QPushButton::pressed, [this, sConsumo,lineType, lineDescr, lineVal, lineMin, lineMax, lineOtt]() {
            mod->aggiornaSens(sConsumo, lineType, lineDescr, lineVal, lineMin, lineMax);
            mod->modificaSensoreConsumo(sConsumo, lineOtt);
        });
    }

    void SensorInfoVisitor::modSMotore(SensoreMotore* sMotore){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel* titolo = new QLabel("Modifica delle informazioni di: " + QString::fromStdString(sMotore->getNome()));
        titolo->setStyleSheet("font: 18px bold;");
        QLabel *labeltype = new QLabel("Tipologia:");
        labeltype->setStyleSheet("font: italic 14px;");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        labeldescr->setStyleSheet("font: italic 14px;");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        labelmin->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        labelmax->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        labelval->setStyleSheet("font: italic 14px;");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelCav = new QLabel("Cavalli:");
        labelCav->setStyleSheet("font: italic 14px;");
        QLineEdit* lineCav = new QLineEdit(widget);

        std::vector<double> v = sMotore->getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sMotore->getTipo()));
        lineDescr->setText(QString::fromStdString(sMotore->getDescrizione()));
        lineMin->setText(QString::number(sMotore->getMin()));
        lineMax->setText(QString::number(sMotore->getMax()));
        lineVal->setText(qval);
        lineCav->setText(QString::number(sMotore->getCavalli()));

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineCav->setFixedWidth(fieldWidth);

        modLayout->addWidget(titolo, 0, Qt::AlignCenter);
        modLayout->addWidget(labeltype);
        modLayout->addWidget(lineType, 0, Qt::AlignLeft);

        modLayout->addWidget(labeldescr);
        modLayout->addWidget(lineDescr, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmin);
        modLayout->addWidget(lineMin, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmax);
        modLayout->addWidget(lineMax, 0, Qt::AlignLeft);

        modLayout->addWidget(labelval);
        modLayout->addWidget(lineVal, 0, Qt::AlignLeft);

        modLayout->addWidget(labelCav);
        modLayout->addWidget(lineCav, 0, Qt::AlignLeft);

        confirmButton = new QPushButton("Conferma", widget);

        QPushButton::connect(confirmButton, &QPushButton::pressed, [this, sMotore,lineType, lineDescr, lineVal, lineMin, lineMax, lineCav]() {
            mod->aggiornaSens(sMotore, lineType, lineDescr, lineVal, lineMin, lineMax);
            mod->modificaSensoreMotore(sMotore, lineCav);
        });
    }

    void SensorInfoVisitor::modSBatteria(SensoreBatteria* sBatteria){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel* titolo = new QLabel("Modifica delle informazioni di: " + QString::fromStdString(sBatteria->getNome()));
        titolo->setStyleSheet("font: 18px bold;");
        QLabel *labeltype = new QLabel("Tipologia:");
        labeltype->setStyleSheet("font: italic 14px;");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        labeldescr->setStyleSheet("font: italic 14px;");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        labelmin->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        labelmax->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        labelval->setStyleSheet("font: italic 14px;");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelMat = new QLabel("Materiale:");
        labelMat->setStyleSheet("font: italic 14px;");
        QLineEdit* lineMat = new QLineEdit(widget);

        std::vector<double> v = sBatteria->getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sBatteria->getTipo()));
        lineDescr->setText(QString::fromStdString(sBatteria->getDescrizione()));
        lineMin->setText(QString::number(sBatteria->getMin()));
        lineMax->setText(QString::number(sBatteria->getMax()));
        lineVal->setText(qval);
        lineMat->setText(QString::fromStdString(sBatteria->getMateriale()));

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineMat->setFixedWidth(fieldWidth);

        modLayout->addWidget(titolo, 0, Qt::AlignCenter);
        modLayout->addWidget(labeltype);
        modLayout->addWidget(lineType, 0, Qt::AlignLeft);

        modLayout->addWidget(labeldescr);
        modLayout->addWidget(lineDescr, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmin);
        modLayout->addWidget(lineMin, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmax);
        modLayout->addWidget(lineMax, 0, Qt::AlignLeft);

        modLayout->addWidget(labelval);
        modLayout->addWidget(lineVal, 0, Qt::AlignLeft);

        modLayout->addWidget(labelMat);
        modLayout->addWidget(lineMat, 0, Qt::AlignLeft);

        confirmButton = new QPushButton("Conferma", widget);

        QPushButton::connect(confirmButton, &QPushButton::pressed, [this, sBatteria,lineType, lineDescr, lineVal, lineMin, lineMax, lineMat]() {
            mod->aggiornaSens(sBatteria, lineType, lineDescr, lineVal, lineMin, lineMax);
            mod->modificaSensoreBatteria(sBatteria, lineMat);
        });
    }

    void SensorInfoVisitor::modSGas(SensoreGas* sGas){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel* titolo = new QLabel("Modifica delle informazioni di: " + QString::fromStdString(sGas->getNome()));
        titolo->setStyleSheet("font: 18px bold;");
        QLabel *labeltype = new QLabel("Tipologia:");
        labeltype->setStyleSheet("font: italic 14px;");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        labeldescr->setStyleSheet("font: italic 14px;");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        labelmin->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        labelmax->setStyleSheet("font: italic 14px;");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        labelval->setStyleSheet("font: italic 14px;");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelImpronta = new QLabel("Impronta ecologica:");
        labelImpronta->setStyleSheet("font: italic 14px;");
        QLineEdit* lineImpronta = new QLineEdit(widget);

        std::vector<double> v = sGas->getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sGas->getTipo()));
        lineDescr->setText(QString::fromStdString(sGas->getDescrizione()));
        lineMin->setText(QString::number(sGas->getMin()));
        lineMax->setText(QString::number(sGas->getMax()));
        lineVal->setText(qval);
        lineImpronta->setText(QString::number(sGas->getImpronta()));

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineImpronta->setFixedWidth(fieldWidth);

        modLayout->addWidget(titolo, 0, Qt::AlignCenter);
        modLayout->addWidget(labeltype);
        modLayout->addWidget(lineType, 0, Qt::AlignLeft);

        modLayout->addWidget(labeldescr);
        modLayout->addWidget(lineDescr, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmin);
        modLayout->addWidget(lineMin, 0, Qt::AlignLeft);

        modLayout->addWidget(labelmax);
        modLayout->addWidget(lineMax, 0, Qt::AlignLeft);

        modLayout->addWidget(labelval);
        modLayout->addWidget(lineVal, 0, Qt::AlignLeft);

        modLayout->addWidget(labelImpronta);
        modLayout->addWidget(lineImpronta, 0, Qt::AlignLeft);


        confirmButton = new QPushButton("Conferma", widget);

        QPushButton::connect(confirmButton, &QPushButton::pressed, [this, sGas,lineType, lineDescr, lineVal, lineMin, lineMax, lineImpronta]() {
            mod->aggiornaSens(sGas, lineType, lineDescr, lineVal, lineMin, lineMax);
            mod->modificaSensoreGas(sGas, lineImpronta);
        });
    }


    void SensorInfoVisitor::saveSPneumatico(SensorePneumatico& sPneumatico, QJsonObject* ob){
        (*ob)["Marca Pneumatico"] = QString::fromStdString(sPneumatico.getMarcaPneu());
        (*ob)["Eta Pneumatico"] = QString::number(sPneumatico.getEta());
    }

    void SensorInfoVisitor::saveSConsumo(SensoreConsumo& sConsumo,QJsonObject* ob){
        (*ob)["Ottano"] = QString::number(sConsumo.getOttano());
    }

    void SensorInfoVisitor::saveSMotore(SensoreMotore& sMotore,QJsonObject* ob){
        (*ob)["Cavalli"] = QString::number(sMotore.getCavalli());
    }

    void SensorInfoVisitor::saveSBatteria(SensoreBatteria& sBatteria,QJsonObject* ob){
        (*ob)["Materiale"] = QString::fromStdString(sBatteria.getMateriale());
    }

    void SensorInfoVisitor::saveSGas(SensoreGas& sGas,QJsonObject* ob){
        (*ob)["Impronta"] = QString::number(sGas.getImpronta());
    }

}
