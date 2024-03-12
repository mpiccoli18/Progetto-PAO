#include "SensorInfoVisitor.h"

namespace sensore{

    QWidget* SensorInfoVisitor::getWidget() {
        return widget;
    }

    void SensorInfoVisitor::visitSPneumatico(SensorePneumatico& sPneumatico) {
        QLabel *labelMarca = new QLabel("Marca Pneumatico: " + QString::fromStdString(sPneumatico.getMarcaPneu()));
        QLabel *labelAge = new QLabel("Tempo di vita: " + QString::number(sPneumatico.getEta()));

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
        widget = new QLabel("Materiali: " +  QString::fromStdString(sBatteria.getMateriale()));
    }

    void SensorInfoVisitor::visitSGas(SensoreGas& sGas) {
        widget = new QLabel("Impronta: " +  QString::number(sGas.getImpronta()));
    }

    void SensorInfoVisitor::modSPneumatico(SensorePneumatico& sPneumatico, modello* m){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel *labeltype = new QLabel("Tipologia:");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelMarca = new QLabel("Marca:");
        QLineEdit* lineMarca = new QLineEdit(widget);

        QLabel *labelEta = new QLabel("Tempo di vita:");
        QLineEdit *lineEta = new QLineEdit(widget);

        std::vector<double> v = sPneumatico.getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sPneumatico.getTipo()));
        lineDescr->setText(QString::fromStdString(sPneumatico.getDescrizione()));
        lineMin->setText(QString::number(sPneumatico.getMin()));
        lineMax->setText(QString::number(sPneumatico.getMax()));
        lineVal->setText(qval);
        lineMarca->setText(QString::fromStdString(sPneumatico.getMarcaPneu()));
        lineEta->setText(QString::number(sPneumatico.getEta()));

        modLayout->addWidget(lineType);
        modLayout->addWidget(lineDescr);
        modLayout->addWidget(lineMin);
        modLayout->addWidget(lineMax);
        modLayout->addWidget(lineVal);
        modLayout->addWidget(lineMarca);
        modLayout->addWidget(lineEta);

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineMarca->setFixedWidth(fieldWidth);
        lineEta->setFixedWidth(fieldWidth);

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

        QPushButton *confirmButton = new QPushButton("Conferma", widget);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        connect(confirmButton, &QPushButton::pressed, this, [this, sPneumatico, lineType, lineDescr, lineVal, lineMin, lineMax]() {
            m->aggiornaSens(s, lineType, lineDescr, lineVal, lineMin, lineMax);
        });
    }

    void SensorInfoVisitor::modSConsumo(SensoreConsumo& sConsumo, modello* m){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel *labeltype = new QLabel("Tipologia:");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelOtt = new QLabel("Numero di ottano:");
        QLineEdit* lineOtt = new QLineEdit(widget);

        std::vector<double> v = sConsumo.getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sConsumo.getTipo()));
        lineDescr->setText(QString::fromStdString(sConsumo.getDescrizione()));
        lineMin->setText(QString::number(sConsumo.getMin()));
        lineMax->setText(QString::number(sConsumo.getMax()));
        lineVal->setText(qval);
        lineOtt->setText(QString::number(sConsumo.getOttano()));

        modLayout->addWidget(lineType);
        modLayout->addWidget(lineDescr);
        modLayout->addWidget(lineMin);
        modLayout->addWidget(lineMax);
        modLayout->addWidget(lineVal);
        modLayout->addWidget(lineOtt);

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineOtt->setFixedWidth(fieldWidth);

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

        QPushButton *confirmButton = new QPushButton("Conferma", widget);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        /*connect(confirmButton, &QPushButton::pressed, this, [this, s, lineType, lineDescr, lineVal, lineMin, lineMax]() {
            mod->aggiornaSens(s, lineType, lineDescr, lineVal, lineMin, lineMax);
        });*/
    }

    void SensorInfoVisitor::modSMotore(SensoreMotore& sMotore, modello* m){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel *labeltype = new QLabel("Tipologia:");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelCav = new QLabel("Cavalli:");
        QLineEdit* lineCav = new QLineEdit(widget);

        std::vector<double> v = sMotore.getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sMotore.getTipo()));
        lineDescr->setText(QString::fromStdString(sMotore.getDescrizione()));
        lineMin->setText(QString::number(sMotore.getMin()));
        lineMax->setText(QString::number(sMotore.getMax()));
        lineVal->setText(qval);
        lineCav->setText(QString::number(sMotore.getCavalli()));

        modLayout->addWidget(lineType);
        modLayout->addWidget(lineDescr);
        modLayout->addWidget(lineMin);
        modLayout->addWidget(lineMax);
        modLayout->addWidget(lineVal);
        modLayout->addWidget(lineCav);

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineCav->setFixedWidth(fieldWidth);

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

        QPushButton *confirmButton = new QPushButton("Conferma", widget);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        /*connect(confirmButton, &QPushButton::pressed, this, [this, s, lineType, lineDescr, lineVal, lineMin, lineMax]() {
            mod->aggiornaSens(s, lineType, lineDescr, lineVal, lineMin, lineMax);
        });*/
    }

    void SensorInfoVisitor::modSBatteria(SensoreBatteria& sBatteria, modello* m){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel *labeltype = new QLabel("Tipologia:");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelMat = new QLabel("Materiale:");
        QLineEdit* lineMat = new QLineEdit(widget);

        std::vector<double> v = sBatteria.getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sBatteria.getTipo()));
        lineDescr->setText(QString::fromStdString(sBatteria.getDescrizione()));
        lineMin->setText(QString::number(sBatteria.getMin()));
        lineMax->setText(QString::number(sBatteria.getMax()));
        lineVal->setText(qval);
        lineMat->setText(QString::fromStdString(sBatteria.getMateriale()));

        modLayout->addWidget(lineType);
        modLayout->addWidget(lineDescr);
        modLayout->addWidget(lineMin);
        modLayout->addWidget(lineMax);
        modLayout->addWidget(lineVal);
        modLayout->addWidget(lineMat);

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineMat->setFixedWidth(fieldWidth);

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

        QPushButton *confirmButton = new QPushButton("Conferma", widget);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        /*connect(confirmButton, &QPushButton::pressed, this, [this, s, lineType, lineDescr, lineVal, lineMin, lineMax]() {
            mod->aggiornaSens(s, lineType, lineDescr, lineVal, lineMin, lineMax);
        });*/
    }

    void SensorInfoVisitor::modSGas(SensoreGas& sGas, modello* m){
        widget = new QWidget();
        QVBoxLayout* modLayout = new QVBoxLayout(widget);

        QLabel *labeltype = new QLabel("Tipologia:");
        QLineEdit *lineType = new QLineEdit(widget);

        QLabel *labeldescr = new QLabel("Descrizione:");
        QLineEdit *lineDescr = new QLineEdit(widget);

        QLabel *labelmin = new QLabel("Valore Min:");
        QLineEdit *lineMin = new QLineEdit(widget);

        QLabel *labelmax = new QLabel("Valore Max:");
        QLineEdit *lineMax = new QLineEdit(widget);

        QLabel *labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        QLineEdit *lineVal = new QLineEdit(widget);

        QLabel *labelImpronta = new QLabel("Impronta ecologica:");
        QLineEdit* lineImpronta = new QLineEdit(widget);

        std::vector<double> v = sGas.getValori();

        QString qval = "";
        for(auto i = v.begin(); i != v.end(); ++i){
            qval += QString::number(*i) + ' ';
        }

        lineType->setText(QString::fromStdString(sGas.getTipo()));
        lineDescr->setText(QString::fromStdString(sGas.getDescrizione()));
        lineMin->setText(QString::number(sGas.getMin()));
        lineMax->setText(QString::number(sGas.getMax()));
        lineVal->setText(qval);
        lineImpronta->setText(QString::number(sGas.getImpronta()));

        modLayout->addWidget(lineType);
        modLayout->addWidget(lineDescr);
        modLayout->addWidget(lineMin);
        modLayout->addWidget(lineMax);
        modLayout->addWidget(lineVal);
        modLayout->addWidget(lineImpronta);

        int fieldWidth = widget->width();
        lineType->setFixedWidth(fieldWidth);
        lineDescr->setFixedWidth(fieldWidth);
        lineMin->setFixedWidth(fieldWidth);
        lineMax->setFixedWidth(fieldWidth);
        lineVal->setFixedWidth(fieldWidth);
        lineImpronta->setFixedWidth(fieldWidth);

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


        QPushButton *confirmButton = new QPushButton("Conferma", widget);
        modLayout->addWidget(confirmButton, 0, Qt::AlignLeft);
        /*connect(confirmButton, &QPushButton::pressed, this, [this, s, lineType, lineDescr, lineVal, lineMin, lineMax]() {
            mod->aggiornaSens(s, lineType, lineDescr, lineVal, lineMin, lineMax);
        });*/
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
