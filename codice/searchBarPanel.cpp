#include "searchBarPanel.h"

namespace sensore{
    searchBarPanel::searchBarPanel(modello* m, QWidget* parent): QWidget(parent){
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignTop);

        ricerca = new QLineEdit(this);
        layout->addWidget(ricerca);

        QPushButton* searchButton = new QPushButton("Cerca", this);
        layout->addWidget(searchButton);

        visualizzazione = new QScrollArea();
        visualizzazione->setMinimumSize(450, 300);
        visualizzazione->setWidgetResizable(true);
        scrollVisua = new QWidget();
        scrollayout = new QVBoxLayout();
        scrollVisua->setLayout(scrollayout);
        visualizzazione->setWidget(scrollVisua);
        layout->addWidget(visualizzazione);
        QLabel* empty;
        mod = m;
        if(mod->getInsiemeSens().empty())
        {
            empty = new QLabel("La lista di sensori è vuota, si prega di aggiungerne di nuovi!");
            empty->setStyleSheet("font: bold 16px; color:red;");
            scrollayout->addWidget(empty, 0, Qt::AlignTop);
        }
        else
        {
            QVBoxLayout* sensorContainerLayout = new QVBoxLayout();
            std::vector<Sensore*> searchVet = mod->getInsiemeSens();
            for(int i = 0; i < searchVet.size(); i++) {
                QWidget *sensorInfo = new QWidget();
                sensorInfo->setObjectName("sensorInfo");
                sensorInfo->setStyleSheet("QWidget#sensorInfo {border: 1px solid black;}"
                                          "QWidget#sensorInfo:hover {background-color: lightgrey;}");
                sensorInfo->setFixedHeight(150);
                QVBoxLayout *sensorLayout = new QVBoxLayout();
                sensorLayout->setContentsMargins(10, 10, 10, 10);
                sensorInfo->setLayout(sensorLayout);
                QLabel *nome = new QLabel("Nome: " + QString::fromStdString(searchVet[i]->getNome()));
                nome->setStyleSheet("font: bold 14px;");
                sensorLayout->addWidget(nome);
                QLabel *tipo = new QLabel("Tipo: " + QString::fromStdString(searchVet[i]->getTipo()));
                sensorLayout->addWidget(tipo);
                QLabel *descrizione = new QLabel("Descrizione: " + QString::fromStdString(searchVet[i]->getDescrizione()));
                sensorLayout->addWidget(descrizione);
                QPushButton *visualizza = new QPushButton("Visualizza " + QString::fromStdString(searchVet[i]->getNome()));
                connect(visualizza, &QPushButton::pressed, this, [this, searchVet, i](){ emit StartView(searchVet[i]); });
                sensorLayout->addWidget(visualizza);
                sensorContainerLayout->addWidget(sensorInfo);
            }
            scrollayout->addLayout(sensorContainerLayout);
            scrollayout->addStretch();
        }
        connect(searchButton, &QPushButton::pressed, this, &searchBarPanel::StartSearch);
        connect(this, &searchBarPanel::StartSearch, this, &searchBarPanel::Search);
    }

    void searchBarPanel::Search(){
        QLayoutItem* item;
        while ((item = scrollayout->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        if(risultati)
        {
            this->layout()->removeWidget(risultati);
            delete risultati;
            risultati = nullptr;
        }
        risultati = new QWidget();
        QVBoxLayout *searchLayout = new QVBoxLayout();
        risultati->setLayout(searchLayout);
        std::string search = (this->ricerca->text()).toStdString();
        std::vector<Sensore*> searchVet = mod->getInsiemeSens();
        bool trovato = false;
        QLabel* empty;
        if(mod->getInsiemeSens().empty())
        {
            empty = new QLabel("La lista di sensori è vuota, si prega di aggiungerne di nuovi!");
            empty->setStyleSheet("font: bold 16px; color:red;");
            scrollayout->addWidget(empty, 0, Qt::AlignTop);
        }
        else
        {
            for(int i = 0; i < searchVet.size(); i++) {
                QString searchStr = QString::fromStdString(searchVet[i]->getNome());
                if(search != "" && (searchVet[i]->getNome() == search || searchStr.contains(QString::fromStdString(search), Qt::CaseInsensitive)))
                {
                    QWidget *sensorInfo = new QWidget();
                    sensorInfo->setObjectName("sensorInfo");
                    sensorInfo->setStyleSheet("QWidget#sensorInfo {border: 1px solid black;}"
                                              "QWidget#sensorInfo:hover {background-color: lightgrey;}");
                    sensorInfo->setFixedHeight(150);
                    QVBoxLayout *sensorLayout = new QVBoxLayout();
                    sensorInfo->setLayout(sensorLayout);
                    QLabel *nome = new QLabel("Nome: " + QString::fromStdString(searchVet[i]->getNome()));
                    nome->setStyleSheet("font: bold 14px;");
                    sensorLayout->addWidget(nome);
                    QLabel *tipo = new QLabel("Tipo: " + QString::fromStdString(searchVet[i]->getTipo()));
                    sensorLayout->addWidget(tipo);
                    QLabel *descrizione = new QLabel("Descrizione: " + QString::fromStdString(searchVet[i]->getDescrizione()));
                    sensorLayout->addWidget(descrizione);
                    QPushButton *visualizza = new QPushButton("Visualizza " + QString::fromStdString(searchVet[i]->getNome()));
                    connect(visualizza, &QPushButton::pressed, this, [this, searchVet, i](){ emit StartView(searchVet[i]); });
                    sensorLayout->addWidget(visualizza);
                    scrollayout->addWidget(sensorInfo, 0, Qt::AlignTop);
                    trovato = true;
                }
            }
            if(search != "" && trovato == false && !mod->getInsiemeSens().empty())
            {
                QMessageBox::warning(this, tr("Attenzione:"), tr("La ricerca non ha prodotto risultati!"));
            }
        }
        this->layout()->addWidget(risultati);
    }
}
