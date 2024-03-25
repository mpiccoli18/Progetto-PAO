#include "homePanel.h"
#include <vector>

namespace sensore{
homePanel::homePanel(QWidget* p):  QWidget(p), grafico(nullptr), modifica(nullptr), creazione(nullptr), modificato(false), sceltaGrafico(nullptr), comandiZoom(nullptr), legenda(nullptr), zoomGrafico(0), elimina(nullptr)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        QGridLayout* menu = new QGridLayout();

        layout->addLayout(menu);
        layoutApp = new QHBoxLayout();
        layout->addLayout(layoutApp);

        QPushButton* save = new QPushButton("Salva con nome");
        save->setShortcut(QKeySequence("Ctrl+N"));
        save->setObjectName("buttonSave");
        save->setStyleSheet("QPushButton#buttonSave {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                            "QPushButton#buttonSave:hover{background-color: lightgrey;}");
        save->setFixedWidth(125);
        menu->addWidget(save, 0, 0, 1, 1);
        connect(save, &QPushButton::pressed, this, &homePanel::SegnaleSalva);
        connect(this, &homePanel::SegnaleSalva, this, &homePanel::Salva);

        salvaStessoFile = new QPushButton("Salva");
        salvaStessoFile->setShortcut(QKeySequence("Ctrl+S"));
        salvaStessoFile->setObjectName("buttonSaveStesso");
        salvaStessoFile->setStyleSheet("QPushButton#buttonSaveStesso {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                      "QPushButton#buttonSaveStesso:hover{background-color: lightgrey;}");
        salvaStessoFile->setFixedWidth(125);
        menu->addWidget(salvaStessoFile, 0, 2, 1, 1);
        salvaStessoFile->setEnabled(false);
        connect(salvaStessoFile, &QPushButton::pressed, this, &homePanel::SegnaleSalvaStessoFile);
        connect(this, &homePanel::SegnaleSalvaStessoFile, this, &homePanel::SalvaStessoFile);

        QPushButton* open = new QPushButton("Apri");
        open->setShortcut(QKeySequence("Ctrl+O"));
        open->setObjectName("buttonOpen");
        open->setStyleSheet("QPushButton#buttonOpen {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                            "QPushButton#buttonOpen:hover{background-color: lightgrey;}");
        open->setFixedWidth(125);
        menu->addWidget(open, 0, 3, 1, 1);
        connect(open, &QPushButton::pressed, this, &homePanel::SegnaleApri);
        connect(this, &homePanel::SegnaleApri, this, &homePanel::Apri);

        QPushButton* create = new QPushButton("Crea");
        create->setShortcut(QKeySequence("Ctrl+C"));
        create->setObjectName("buttonCreate");
        create->setStyleSheet("QPushButton#buttonCreate {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                              "QPushButton#buttonCreate:hover{background-color: lightgrey;}");
        create->setFixedWidth(125);
        menu->addWidget(create, 0, 4, 1, 1);
        connect(create, &QPushButton::pressed, this, &homePanel::SegnaleCrea);
        connect(this, &homePanel::SegnaleCrea, this, &homePanel::Crea);

        QSpacerItem *spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        menu->addItem(spacer, 0, 5, 1, 1);

        mod = new modello();
        barraRicerca = new searchBarPanel(mod);// barra di ricerca
        layoutApp->addWidget(barraRicerca,1);

        pannello = new SensorPanel();// sensore
        pannello->setStyleSheet("background-color:darkgrey;");
        layoutApp->addWidget(pannello,2);

        layoutApp->setStretch(0, 1);
        layoutApp->setStretch(1, 2);

        connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
        connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
        connect(this, &homePanel::SegnaleSensoreSelezionato, this, &homePanel::SensoreSelezionato);
    }

    void homePanel::Apri(){
        if(creazione){
            layoutApp->layout()->removeWidget(creazione);
            delete creazione;
            creazione = nullptr;

            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(mod);
            pannello = new SensorPanel();
            layoutApp->addWidget(barraRicerca, 1);
            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
            connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
            connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
            connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
        }
        if(modificato == true && !(nomeFile.isEmpty()))
        {
            QWidget *noModifiche = new QWidget();
            QVBoxLayout *modificheLayout = new QVBoxLayout();
            noModifiche->setLayout(modificheLayout);
            noModifiche->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            QLabel* mod = new QLabel("Attenzione: hai delle modifiche non salvate!");
            mod->setStyleSheet("font: bold 16px; margin-bottom: 8px;");
            modificheLayout->addWidget(mod);
            QPushButton* salva = new QPushButton("Salva");
            salva->setObjectName("salvaMod");
            salva->setStyleSheet("QPushButton#salvaMod {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                 "QPushButton#salvaMod:hover{background-color: lightgrey;}");

            QPushButton* annulla = new QPushButton("Annulla");
            annulla->setObjectName("annullaM");
            annulla->setStyleSheet("QPushButton#annullaM {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                   "QPushButton#annullaM:hover{background-color: red;}");
            modificheLayout->addWidget(salva);
            modificheLayout->addWidget(annulla);
            connect(salva, &QPushButton::pressed, this, [=]{
                SalvaStessoFile();
                noModifiche->close();
                modificato = false;
            });
            connect(annulla, &QPushButton::pressed, this, [=] {
                noModifiche->close();
            });
            noModifiche->show();
        }
        else if(modificato == true)
        {
            QWidget *noModifiche = new QWidget();
            QVBoxLayout *modificheLayout = new QVBoxLayout();
            noModifiche->setLayout(modificheLayout);
            QLabel* mod = new QLabel("Attenzione: hai delle modifiche non salvate!");
            mod->setStyleSheet("font: bold 16px; margin-bottom: 8px;");
            modificheLayout->addWidget(mod);
            QPushButton* salva = new QPushButton("Salva con nome");
            salva->setObjectName("salvaMod");
            salva->setStyleSheet("QPushButton#salvaMod {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                 "QPushButton#salvaMod:hover{background-color: lightgrey;}");

            QPushButton* annulla = new QPushButton("Annulla");
            annulla->setObjectName("annullaM");
            annulla->setStyleSheet("QPushButton#annullaM {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                   "QPushButton#annullaM:hover{background-color: red;}");

            modificheLayout->addWidget(salva);
            modificheLayout->addWidget(annulla);
            noModifiche->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
            connect(salva, &QPushButton::pressed, this, [=]{
                Salva();
                noModifiche->close();
                modificato = false;
            });
            connect(annulla, &QPushButton::pressed, this, [=] {
                noModifiche->close();
            });
            noModifiche->show();
        }
        else
        {
            QString filePath = QFileDialog::getOpenFileName(this, tr("Apri file JSON"), "", tr("File JSON (*.json)"));
            nomeFile = filePath;
            if(!(nomeFile.isEmpty()))
            {
                mod->pulisciInsieme();
            }
            int warning = mod->apriSens(filePath);
            if(warning == 1)
            {
                QMessageBox::warning(this, tr("Errore"), tr("Il file selezionato è vuoto!"));
                return;
            }
            if(warning == 2)
            {
                QMessageBox::warning(this, tr("Errore"), tr("Impossibile aprire il file"));
                return;
            }
            if(warning == 3)
            {
                QMessageBox::warning(this, tr("Errore"), tr("Il file non contiene un oggetto JSON valido."));
                return;
            }
            QMessageBox::information(this, tr("Successo"), tr("Sensori caricati con successo!"));

        }
        if(barraRicerca)
        {
            delete barraRicerca;
            delete pannello;
            barraRicerca = new searchBarPanel(mod);
            pannello = new SensorPanel();
            layoutApp->addWidget(barraRicerca, 1);
            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
            connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
            connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
            connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
        }
    }

    void homePanel::Salva(){

        QString filePath = QFileDialog::getSaveFileName(this, tr("Salva file JSON"), "", tr("File JSON (*.json)"));

        int warning = mod->salvaSens(filePath);

        if(warning == 1)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Il file selezionato è vuoto!"));
            return;
        }
        if(warning == 2)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile creare il file!"));
            return;
        }
        if(!(filePath.isEmpty()))
        {
            modificato = false;
        }
        QMessageBox::information(this, tr("Successo"), tr("Dati salvati nel file JSON: ") + filePath);
    }

    void homePanel::SalvaStessoFile(){

        int warning = mod->salvaSens(nomeFile);

        if(warning == 1)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Il file selezionato è vuoto!"));
            return;
        }
        if(warning == 2)
        {
            QMessageBox::warning(this, tr("Errore"), tr("Impossibile creare il file!"));
            return;
        }
        QMessageBox::information(this, tr("Successo"), tr("Dati salvati nel file JSON: ") + nomeFile);
        salvaStessoFile->setEnabled(false);
        modificato = false;
    }

    void homePanel::Crea() {
        if(barraRicerca){
            layoutApp->layout()->removeWidget(barraRicerca);
            if (grafico) {
                pannello->layout()->removeWidget(grafico);
                if (comandiZoom) {
                    pannello->layout()->removeWidget(comandiZoom);
                    delete comandiZoom;
                    comandiZoom = nullptr;
                }
                if (sceltaGrafico) {
                    pannello->layout()->removeWidget(sceltaGrafico);
                    delete sceltaGrafico;
                    sceltaGrafico = nullptr;
                }
                delete grafico;
                grafico = nullptr;
            }
            delete pannello;
            pannello = nullptr;
            delete barraRicerca;
            barraRicerca = nullptr;
        }
        if(creazione)
        {
            layoutApp->layout()->removeWidget(creazione);
            delete creazione;
            creazione = nullptr;
        }
        barraRicerca = new searchBarPanel(mod);
        connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);

        creazione = new QWidget();
        QVBoxLayout* createLayout = new QVBoxLayout();
        creazione->setLayout(createLayout);
        QLabel* labeltitle = new QLabel("Creazione di un Sensore");
        labeltitle->setAlignment(Qt::AlignCenter);
        labeltitle->setStyleSheet("font: bold 18px;");
        createLayout->addWidget(labeltitle);

        QLabel* labeltype = new QLabel("Tipologia:");
        labeltype->setStyleSheet("font: italic 14px;");
        QLineEdit* lineType = new QLineEdit(creazione);

        QLabel* labeldescr = new QLabel("Descrizione (max 100 caratteri):");
        labeldescr->setStyleSheet("font: italic 14px;");
        QLineEdit* lineDescr = new QLineEdit(creazione);

        QLabel* labelmin = new QLabel("Valore minimo:");
        labelmin->setStyleSheet("font: italic 14px;");
        QLineEdit* lineMin = new QLineEdit(creazione);

        QLabel* labelmax = new QLabel("Valore massimo:");
        labelmax->setStyleSheet("font: italic 14px;");
        QLineEdit* lineMax = new QLineEdit(creazione);

        QLabel* labelval = new QLabel("Valori del Sensore (separati da uno spazio):");
        labelval->setStyleSheet("font: italic 14px;");
        QLineEdit* lineVal = new QLineEdit(creazione);

        createLayout->addWidget(labeltype, 0, Qt::AlignTop);
        createLayout->addWidget(lineType, 0, Qt::AlignTop);
        createLayout->addWidget(labeldescr, 0, Qt::AlignTop);
        createLayout->addWidget(lineDescr, 0, Qt::AlignTop);
        createLayout->addWidget(labelmin, 0, Qt::AlignTop);
        createLayout->addWidget(lineMin, 0, Qt::AlignTop);
        createLayout->addWidget(labelmax, 0, Qt::AlignTop);
        createLayout->addWidget(lineMax, 0, Qt::AlignTop);
        createLayout->addWidget(labelval, 0, Qt::AlignTop);
        createLayout->addWidget(lineVal, 0, Qt::AlignTop);

        QComboBox* sensorTypeComboBox = new QComboBox();
        sensorTypeComboBox->setObjectName("comboBoxCrea");
        sensorTypeComboBox->setStyleSheet("QComboBox#comboBoxCrea {border: 1px solid black; padding: 4px; background-color:transparent;}");
        sensorTypeComboBox->addItem("Scegli il tipo del Sensore:");
        sensorTypeComboBox->setItemData(0, QVariant(0), Qt::UserRole - 1);
        sensorTypeComboBox->addItem("Sensore Consumo");
        sensorTypeComboBox->addItem("Sensore Motore");
        sensorTypeComboBox->addItem("Sensore Batteria");
        sensorTypeComboBox->addItem("Sensore Gas");
        sensorTypeComboBox->addItem("Sensore Pneumatico");

        createLayout->addWidget(sensorTypeComboBox);
        createLayout->addStretch();

        connect(sensorTypeComboBox, QOverload<int>::of(&QComboBox::activated), [=](int index) {
                QString selectedOption = sensorTypeComboBox->itemText(index);
                emit SegnaleSensoreSelezionato(lineType, lineDescr, lineMin, lineMax, lineVal, selectedOption, createLayout);
        });

        layoutApp->addWidget(barraRicerca, 1);
        layoutApp->addWidget(creazione, 2);
        layoutApp->setStretch(0, 1);
        layoutApp->setStretch(1, 2);
    }

    void homePanel::SensoreSelezionato(QLineEdit* lineType, QLineEdit* lineDescr, QLineEdit* lineMin, QLineEdit* lineMax, QLineEdit* lineVal, const QString& selectedSensor, QVBoxLayout* createLayout)
    {
        while (createLayout->count() > 12) {
            QLayoutItem* item = createLayout->takeAt(12);
            delete item->widget();
            delete item;
        }

        if (selectedSensor == "Sensore Batteria") {
            QLabel* labelmat = new QLabel("Materiali:");
            labelmat->setStyleSheet("font: italic 14px;");
            QLineEdit* lineMat = new QLineEdit(creazione);
            lineMat->setStyleSheet("border: 1px solid black");
            createLayout->addWidget(labelmat, 0, Qt::AlignTop);
            createLayout->addWidget(lineMat, 0, Qt::AlignTop);
            QPushButton* confirmButton = new QPushButton("Conferma");
            confirmButton->setObjectName("confermaCrea");
            confirmButton->setStyleSheet("QPushButton#confermaCrea {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                         "QPushButton#confermaCrea:hover{background-color: lightgrey;}");
            createLayout->addWidget(confirmButton);
            createLayout->addStretch();
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineMat]() {
                QString d = lineDescr->text();
                if(d.size() > 100)
                {
                    QMessageBox::warning(this, tr("Attenzione"), tr("La descrizione supera i 100 caratteri, riprovare!"));
                }
                else
                {
                    mod->creaSensBatteria(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineMat);
                    if(barraRicerca)
                    {
                        delete barraRicerca;
                        delete creazione;
                        creazione = nullptr;
                        barraRicerca = new searchBarPanel(mod);
                        pannello = new SensorPanel();
                        layoutApp->addWidget(barraRicerca, 1);
                        layoutApp->addWidget(pannello, 2);
                        layoutApp->setStretch(0, 1);
                        layoutApp->setStretch(1, 2);
                        connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
                        connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
                        connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
                        connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
                    }
                    if(!nomeFile.isEmpty())
                    {
                        salvaStessoFile->setEnabled(true);
                    }
                    modificato = true;
                    QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
                }
            });
        }
        if (selectedSensor == "Sensore Consumo") {
            QLabel* labelott = new QLabel("Numero di Ottano:");
            labelott->setStyleSheet("font: italic 14px;");
            QLineEdit* lineOtt = new QLineEdit(creazione);
            lineOtt->setStyleSheet("border: 1px solid black");
            createLayout->addWidget(labelott, 0, Qt::AlignTop);
            createLayout->addWidget(lineOtt, 0, Qt::AlignTop);

            QPushButton* confirmButton = new QPushButton("Conferma");
            confirmButton->setObjectName("confermaCrea");
            confirmButton->setStyleSheet("QPushButton#confermaCrea {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                         "QPushButton#confermaCrea:hover{background-color: lightgrey;}");
            createLayout->addWidget(confirmButton);
            createLayout->addStretch();
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineOtt]() {
                QString d = lineDescr->text();
                if(d.size() > 100)
                {
                    QMessageBox::warning(this, tr("Attenzione"), tr("La descrizione supera i 100 caratteri, riprovare!"));
                }
                else
                {
                    mod->creaSensConsumo(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineOtt);
                    if(barraRicerca)
                    {
                        delete barraRicerca;
                        delete creazione;
                        creazione = nullptr;
                        barraRicerca = new searchBarPanel(mod);
                        pannello = new SensorPanel();
                        layoutApp->addWidget(barraRicerca, 1);
                        layoutApp->addWidget(pannello, 2);
                        layoutApp->setStretch(0, 1);
                        layoutApp->setStretch(1, 2);
                        connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
                        connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
                        connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
                        connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
                    }
                    if(!nomeFile.isEmpty())
                    {
                        salvaStessoFile->setEnabled(true);
                    }
                    modificato = true;
                    QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
                }
            });
        }
        if (selectedSensor == "Sensore Motore") {
            QLabel* labelcav = new QLabel("Numero di Cavalli:");
            labelcav->setStyleSheet("font: italic 14px;");
            QLineEdit* lineCav = new QLineEdit(creazione);
            lineCav->setStyleSheet("border: 1px solid black");
            createLayout->addWidget(labelcav, 0, Qt::AlignTop);
            createLayout->addWidget(lineCav, 0, Qt::AlignTop);

            QPushButton* confirmButton = new QPushButton("Conferma");
            confirmButton->setObjectName("confermaCrea");
            confirmButton->setStyleSheet("QPushButton#confermaCrea {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                         "QPushButton#confermaCrea:hover{background-color: lightgrey;}");
            createLayout->addWidget(confirmButton);
            createLayout->addStretch();
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineCav]() {
                QString d = lineDescr->text();
                if(d.size() > 100)
                {
                    QMessageBox::warning(this, tr("Attenzione"), tr("La descrizione supera i 100 caratteri, riprovare!"));
                }
                else
                {
                    mod->creaSensMotore(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineCav);
                    if(barraRicerca)
                    {
                        delete barraRicerca;
                        delete creazione;
                        creazione = nullptr;
                        barraRicerca = new searchBarPanel(mod);
                        pannello = new SensorPanel();
                        layoutApp->addWidget(barraRicerca, 1);
                        layoutApp->addWidget(pannello, 2);
                        layoutApp->setStretch(0, 1);
                        layoutApp->setStretch(1, 2);
                        connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
                        connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
                        connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
                        connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
                    }
                    if(!nomeFile.isEmpty())
                    {
                        salvaStessoFile->setEnabled(true);
                    }
                    modificato = true;
                    QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
                }
            });
        }
        if (selectedSensor == "Sensore Gas") {
            QLabel* labelfootp = new QLabel("Impronta:");
            labelfootp->setStyleSheet("font: italic 14px;");
            QLineEdit* lineFootp = new QLineEdit(creazione);
            lineFootp->setStyleSheet("border: 1px solid black");
            createLayout->addWidget(labelfootp, 0, Qt::AlignTop);
            createLayout->addWidget(lineFootp, 0, Qt::AlignTop);

            QPushButton* confirmButton = new QPushButton("Conferma");
            confirmButton->setObjectName("confermaCrea");
            confirmButton->setStyleSheet("QPushButton#confermaCrea {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                         "QPushButton#confermaCrea:hover{background-color: lightgrey;}");
            createLayout->addWidget(confirmButton);
            createLayout->addStretch();
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineFootp]() {
                QString d = lineDescr->text();
                if(d.size() > 100)
                {
                    QMessageBox::warning(this, tr("Attenzione"), tr("La descrizione supera i 100 caratteri, riprovare!"));
                }
                else
                {
                    mod->creaSensConsumo(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineFootp);
                    if(barraRicerca)
                    {
                        delete barraRicerca;
                        delete creazione;
                        creazione = nullptr;
                        barraRicerca = new searchBarPanel(mod);
                        pannello = new SensorPanel();
                        layoutApp->addWidget(barraRicerca, 1);
                        layoutApp->addWidget(pannello, 2);
                        layoutApp->setStretch(0, 1);
                        layoutApp->setStretch(1, 2);
                        connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
                        connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
                        connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
                        connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
                    }
                    if(!nomeFile.isEmpty())
                    {
                        salvaStessoFile->setEnabled(true);
                    }
                    modificato = true;
                    QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
                }
            });
        }
        if (selectedSensor == "Sensore Pneumatico") {
            QLabel* labelbr = new QLabel("Marca:");
            labelbr->setStyleSheet("font: italic 14px;");
            QLineEdit* lineBr = new QLineEdit(creazione);
            lineBr->setStyleSheet("border: 1px solid black");
            createLayout->addWidget(labelbr, 0, Qt::AlignTop);
            createLayout->addWidget(lineBr, 0, Qt::AlignTop);
            QLabel* labelage = new QLabel("Tempo di vita:");
            labelage->setStyleSheet("font: italic 14px;");
            QLineEdit* lineAge = new QLineEdit(creazione);
            lineAge->setStyleSheet("border: 1px solid black");
            createLayout->addWidget(labelage, 0, Qt::AlignTop);
            createLayout->addWidget(lineAge, 0, Qt::AlignTop);

            QPushButton* confirmButton = new QPushButton("Conferma");
            confirmButton->setObjectName("confermaCrea");
            confirmButton->setStyleSheet("QPushButton#confermaCrea {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                         "QPushButton#confermaCrea:hover{background-color: lightgrey;}");
            createLayout->addWidget(confirmButton);
            createLayout->addStretch();
            connect(confirmButton, &QPushButton::pressed, this, [this, selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineBr, lineAge]() {
                QString d = lineDescr->text();
                if(d.size() > 100)
                {
                    QMessageBox::warning(this, tr("Attenzione"), tr("La descrizione supera i 100 caratteri, riprovare!"));
                }
                else
                {
                    mod->creaSensPneumatico(selectedSensor, lineType, lineDescr, lineVal, lineMin, lineMax, lineAge, lineBr);
                    if(barraRicerca)
                    {
                        delete barraRicerca;
                        delete creazione;
                        creazione = nullptr;
                        barraRicerca = new searchBarPanel(mod);
                        pannello = new SensorPanel();
                        layoutApp->addWidget(barraRicerca, 1);
                        layoutApp->addWidget(pannello, 2);
                        layoutApp->setStretch(0, 1);
                        layoutApp->setStretch(1, 2);
                        connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
                        connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
                        connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
                        connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);

                    }
                    if(!nomeFile.isEmpty())
                    {
                        salvaStessoFile->setEnabled(true);
                    }
                    modificato = true;
                    QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato creato !"));
                }
            });
        }
    }

    void homePanel::Modifica(Sensore *s){
        if(modifica)
        {
            modifica->close();
        }
        SensorInfoVisitor visitor;
        visitor.setModello(mod);
        s->accettaMod(visitor);
        modifica = visitor.getWidget();

        QPushButton* confirmButton = visitor.getPulsante();
        QPushButton *exitButton = new QPushButton("Annulla", modifica);

        modifica->layout()->addWidget(exitButton);
        modifica->layout()->addWidget(confirmButton);
        modifica->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        modifica->show();

        connect(confirmButton, &QPushButton::pressed, this, [=](){
            if (sceltaGrafico) {
                this->pannello->layout()->removeWidget(sceltaGrafico);
                delete sceltaGrafico;
                sceltaGrafico = nullptr;
            }
            if (grafico) {
                this->pannello->layout()->removeWidget(grafico);
                if (comandiZoom) {
                    this->pannello->layout()->removeWidget(comandiZoom);
                    delete comandiZoom;
                    comandiZoom = nullptr;
                }
                delete grafico;
                grafico = nullptr;
            }
            if(modifica){
                delete barraRicerca;
                barraRicerca = new searchBarPanel(mod);
                delete pannello;
                pannello = new SensorPanel(s);
                layoutApp->addWidget(barraRicerca, 1);
                layoutApp->addWidget(pannello, 2);
                layoutApp->setStretch(0, 1);
                layoutApp->setStretch(1, 2);
                connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
                connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
                connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
                connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
            }
            QMessageBox::information(this, tr("Successo"), tr("Il sensore è stato aggiornato!"));
            salvaStessoFile->setEnabled(true);
            modificato = true;
            modifica->close();
        });

        connect(exitButton, &QPushButton::pressed, this, [=](){
            modifica->close();
        });
    }

    void homePanel::Simula(){
        if (grafico) {
            pannello->layout()->removeWidget(grafico);
            if (comandiZoom) {
                pannello->layout()->removeWidget(comandiZoom);
                delete comandiZoom;
                comandiZoom = nullptr;
            }
            if (sceltaGrafico) {
                pannello->layout()->removeWidget(sceltaGrafico);
                delete sceltaGrafico;
                sceltaGrafico = nullptr;
            }
            if (legenda) {
                pannello->layout()->removeWidget(legenda);
                delete legenda;
                legenda = nullptr;
            }
            delete grafico;
            grafico = nullptr;
        }
        std::vector<double> valori = sensoreGenerale->getValori();

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->setTitle("" + QString::fromStdString(sensoreGenerale->getTipo()) + " di: " + QString::fromStdString(sensoreGenerale->getNome()));

        // Asse X
        QValueAxis *axisX = new QValueAxis();
        axisX->setRange(0, valori.size()+1);
        axisX->setTickCount(valori.size()+2);
        axisX->setLabelFormat("%d");
        chart->addAxis(axisX, Qt::AlignBottom);

        // Asse Y
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(sensoreGenerale->getMin(), sensoreGenerale->getMax());
        axisY->setTickCount(10);
        axisY->applyNiceNumbers();
        chart->addAxis(axisY, Qt::AlignLeft);
        chart->setAnimationOptions(QChart::SeriesAnimations);

        sceltaGrafico = new QComboBox();
        sceltaGrafico->setObjectName("comboScelta");
        sceltaGrafico->setStyleSheet("QComboBox#comboScelta {border: 1px solid black; padding: 4px; background-color: transparent;}");
        sceltaGrafico->setFixedWidth(250);
        sceltaGrafico->addItem("Scegli una tipologia di grafico");
        sceltaGrafico->setItemData(0, QVariant(0), Qt::UserRole - 1);
        sceltaGrafico->addItem("Spline");
        sceltaGrafico->addItem("Punti");
        sceltaGrafico->addItem("Linee");
        sceltaGrafico->addItem("Barra");
        connect(sceltaGrafico, QOverload<int>::of(&QComboBox::currentIndexChanged), [=](int index){
            switch(index) {
                case 1: // Spline
                    chart->removeAllSeries();
                    {
                        QSplineSeries* splineGrafico = new QSplineSeries();
                        for (unsigned long long i = 0; i < valori.size(); i++)
                            splineGrafico->append(i + 1, valori[i]);
                        chart->addSeries(splineGrafico);
                        splineGrafico->attachAxis(axisX);
                        splineGrafico->attachAxis(axisY);
                    }
                    break;
                case 2: // Punti
                    chart->removeAllSeries();
                    {
                        QScatterSeries* scatterGrafico = new QScatterSeries();
                        for (unsigned long long i = 0; i < valori.size(); i++)
                            scatterGrafico->append(i + 1, valori[i]);
                        chart->addSeries(scatterGrafico);
                        scatterGrafico->attachAxis(axisX);
                        scatterGrafico->attachAxis(axisY);
                    }
                    break;
                case 3: // Linee
                    chart->removeAllSeries();
                    {
                        QLineSeries *lineGrafico = new QLineSeries();
                        for (unsigned long long i = 0; i < valori.size(); i++)
                            lineGrafico->append(i + 1, valori[i]);
                        chart->addSeries(lineGrafico);
                        lineGrafico->attachAxis(axisX);
                        lineGrafico->attachAxis(axisY);
                    }
                    break;
                case 4: // Barra
                    chart->removeAllSeries();
                    {
                        QBarSeries *barraGrafico = new QBarSeries();
                        QBarSet* set = new QBarSet("Valori");
                        for (unsigned long long i = 0; i < valori.size(); i++) {
                            if(i == 0) *set << 0;
                            *set << valori[i];
                            barraGrafico->append(set);
                        }
                        //barraGrafico->append(set);
                        chart->addSeries(barraGrafico);
                        barraGrafico->attachAxis(axisX);
                        barraGrafico->attachAxis(axisY);
                    }
                    break;
                default:
                    break;
            }
        });

        grafico = new QChartView(chart);
        grafico->setStyleSheet("border: 1px solid black; border-radius: 2px; background-color:lightgrey;");
        grafico->setRenderHint(QPainter::Antialiasing);
        grafico->setMaximumSize(1200, 700);
        comandiZoom = new QPushButton("Mostra/nascondi comandi grafico");
        comandiZoom->setObjectName("comandiZoom");
        comandiZoom->setStyleSheet("QPushButton#comandiZoom {border: 1px solid black; padding: 8px; border-radius: 16px;}"
                                   "QPushButton#comandiZoom:hover {background-color: lightgrey;}");
        comandiZoom->setFixedWidth(250);
        connect(comandiZoom, &QPushButton::clicked, this, &homePanel::MostraNascondiLegenda);
        legenda = new QLabel();
        QString infoText = "Informazioni sui tasti bindati:\n";
        infoText += "Ingrandisci:                  +        ";
        infoText += "Rimpicciolisci:            -\n";
        infoText += "Muoviti a sinistra:        A        ";
        infoText += "Muoviti a destra:        D\n";
        infoText += "Muoviti sopra:             W       ";
        infoText += "Muoviti sotto:             S\n";
        infoText += "Reset:                         Esc\n";
        legenda = new QLabel(infoText);
        legenda->setStyleSheet("font: italic 14px; margin-left: 16px;");
        legenda->setAlignment(Qt::AlignLeft);
        legenda->hide();
        this->pannello->layout()->addWidget(comandiZoom);
        this->pannello->layout()->addWidget(legenda);
        this->pannello->layout()->addWidget(sceltaGrafico);
        this->pannello->layout()->addWidget(grafico);
    }

    void homePanel::MostraNascondiLegenda(){
        if (legenda->isVisible()) {
            legenda->hide();
        } else {
            legenda->show();
        }
    }

    void homePanel::comandiGrafico(QKeyEvent* event)
    {
        if(grafico)
        {
            switch (event->key())
            {
            case Qt::Key_Plus:
                zoomIn();
                break;
            case Qt::Key_Minus:
                zoomOut();
                break;
            case Qt::Key_A:
                spostamentoAsseX(-1);
                break;
            case Qt::Key_D:
                spostamentoAsseX(1);
                break;
            case Qt::Key_W:
                spostamentoAsseY(1);
                break;
            case Qt::Key_S:
                spostamentoAsseY(-1);
                break;
            case Qt::Key_Escape:
                rimozioneZoom();
                break;
            }
        }
    }

    void homePanel::zoomIn()
    {
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        if(zoomGrafico == 0)
        {
            grafico->chart()->zoomIn();
            asseX->setTickCount(7);
            asseX->setRange(1, 7);
        }
        else if(zoomGrafico == 1)
        {
            grafico->chart()->zoomIn();
            asseX->setTickCount(5);
            asseX->setRange(2, 6);
        }
        else if(zoomGrafico == 2)
        {
            grafico->chart()->zoomIn();
            asseX->setTickCount(3);
            asseX->setRange(3, 5);
        }
        else if(zoomGrafico >= 3)
        {
            QMessageBox::warning(this, tr("Attenzione!"), tr("Limite dello zoom raggiunto"));
            zoomGrafico--;
        }
        else
        {
            grafico->chart()->zoomIn();
            asseX->setTickCount(14);
            asseX->setRange(0, 13);
        }
        zoomGrafico++;
    }

    void homePanel::zoomOut()
    {
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        if(zoomGrafico == 3)
        {
            grafico->chart()->zoomOut();
            asseX->setTickCount(5);
            asseX->setRange(2, 6);
        }
        else if(zoomGrafico == 2)
        {
            grafico->chart()->zoomOut();
            asseX->setTickCount(7);
            asseX->setRange(1, 7);
        }
        else if(zoomGrafico == 1)
        {
            grafico->chart()->zoomOut();
            asseX->setTickCount(14);
            asseX->setRange(0, 13);
        }
        else if(zoomGrafico <= -2)
        {
            QMessageBox::warning(this, tr("Attenzione!"), tr("Limite dello zoom raggiunto"));
            zoomGrafico++;
        }
        else
        {
            grafico->chart()->zoomOut();
            asseX->setTickCount(28);
            asseX->setRange(0, 27);
        }
        zoomGrafico--;
    }

    void homePanel::spostamentoAsseX(int direzione)
    {
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        if (!asseX)
            return;
        int min = asseX->min();
        int max = asseX->max();
        asseX->setLabelFormat("%d");
        if(min+direzione >= 0)
        {
            asseX->setRange(min + direzione, max + direzione);
        }
    }

    void homePanel::spostamentoAsseY(int direzione)
    {
        QValueAxis* asseY = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Vertical).at(0));
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        if (!asseY)
            return;

        int val = 0;
        asseX->setLabelFormat("%d");

        if(grafico->chart()->isZoomed())
        {
            val = 5 * direzione;
        }
        else
        { 
            val = 10 * direzione;
        }
        if(asseY->min() + val >= 0)
        {
            asseY->setRange(asseY->min() + val, asseY->max() + val);
        }
    }

    void homePanel::rimozioneZoom()
    {
        grafico->chart()->zoomReset();
        QValueAxis* asseX = qobject_cast<QValueAxis*>(grafico->chart()->axes(Qt::Horizontal).at(0));
        asseX->setLabelFormat("%d");
        asseX->setTickCount(14);
        asseX->setRange(0, 13);
        zoomGrafico = 0;
    }

    void homePanel::Elimina(Sensore* s) {
        if(elimina)
        {
            elimina->close();
        }
        elimina = new QWidget();
        QVBoxLayout* eliminaL = new QVBoxLayout();
        QLabel* eliminaLab = new QLabel("Sei sicuro di voler eliminare questo sensore?");
        eliminaLab->setStyleSheet("font: italic 16px; margin-bottom: 8px;");
        QPushButton *conferma = new QPushButton("Conferma");
        conferma->setObjectName("confermaE");
        conferma->setStyleSheet("QPushButton#confermaE {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                                "QPushButton#confermaE:hover{background-color: lightgrey;}");
        QPushButton *annulla = new QPushButton("Annulla");
        annulla->setObjectName("annullaE");
        annulla->setStyleSheet("QPushButton#annullaE {border: 1px solid black; border-radius: 16px; padding: 8px;} "
                               "QPushButton#annullaE:hover{background-color: red;}");

        elimina->setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
        elimina->setLayout(eliminaL);
        eliminaL->addWidget(eliminaLab);
        eliminaL->addWidget(conferma);
        eliminaL->addWidget(annulla);

        connect(conferma, &QPushButton::pressed, this, [=](){
            if(modifica)
                modifica = nullptr;
            if(grafico)
                grafico = nullptr;
            if(sceltaGrafico)
                sceltaGrafico = nullptr;
            if(comandiZoom)
                sceltaGrafico = nullptr;
            mod->eliminaSens(s);
            sensoreGenerale = nullptr;
            if(pannello)
            {
                delete barraRicerca;
                delete pannello;
                barraRicerca = new searchBarPanel(mod);
                pannello = new SensorPanel();
                layoutApp->addWidget(barraRicerca, 1);
                layoutApp->addWidget(pannello, 2);
                layoutApp->setStretch(0, 1);
                layoutApp->setStretch(1, 2);
                connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
                connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
                connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
                connect(barraRicerca, &searchBarPanel::SegnaleMostra, this, &homePanel::Mostra);
            }
            if(!(nomeFile.isEmpty()))
            {
                salvaStessoFile->setEnabled(true);
            }
            modificato = true;
            elimina->close();
        });

        connect(annulla, &QPushButton::pressed, this, [=](){
            elimina->close();
        });
        elimina->show();
    }


    void homePanel::Mostra(Sensore* s){
        if(pannello)
        {
            this->layout()->removeWidget(pannello);
            if(grafico)
                grafico = nullptr;
            if(sceltaGrafico)
                sceltaGrafico = nullptr;
            if(comandiZoom)
                comandiZoom = nullptr;
            if(modifica)
                modifica = nullptr;

            delete pannello;
            pannello = new SensorPanel(s);
            sensoreGenerale = s;

            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
            connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
            connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
        }
        if(creazione)
        {
            layoutApp->layout()->removeWidget(creazione);
            delete creazione;
            creazione = nullptr;

            pannello = new SensorPanel(s);
            sensoreGenerale = s;

            layoutApp->addWidget(pannello, 2);
            layoutApp->setStretch(0, 1);
            layoutApp->setStretch(1, 2);
            connect(pannello, &SensorPanel::SegnaleSimula, this, &homePanel::Simula);
            connect(pannello, &SensorPanel::SegnaleModifica, this, &homePanel::Modifica);
            connect(pannello, &SensorPanel::SegnaleElimina, this, &homePanel::Elimina);
        }
    }
}
