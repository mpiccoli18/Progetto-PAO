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
        QLabel* empty2;
        mod = m;
        if(mod->getInsiemeSens().empty())
        {
            empty = new QLabel("La lista di sensori è vuota, si prega di aggiungerne di nuovi!");
            empty->setStyleSheet("font: bold 16px; color:red;");
            empty2 = new QLabel("Per aggiungere nuovi sensori premi i pulsanti 'Apri' o 'Crea' in alto!");
            empty2->setStyleSheet("font: bold 14px; color:black;");
            scrollayout->addWidget(empty, 0, Qt::AlignTop);
            scrollayout->addWidget(empty2, 1, Qt::AlignTop);
        }
        else
        {
            std::vector<Sensore*> searchVet = mod->getInsiemeSens();
            for(int i = 0; i < searchVet.size(); i++) {
                QWidget *sensorInfo = new QWidget();
                sensorInfo->setObjectName("sensorInfo");
                sensorInfo->setStyleSheet("QWidget#sensorInfo {border: 1px solid black;}");
                sensorInfo->setFixedHeight(150);
                QVBoxLayout *sensorLayout = new QVBoxLayout();
                sensorLayout->setContentsMargins(10, 10, 10, 10);
                sensorInfo->setLayout(sensorLayout);
                QLabel *nome = new QLabel("Nome: " + QString::fromStdString(searchVet[i]->getNome()));
                nome->setStyleSheet("font: bold 14px;");
                sensorLayout->addWidget(nome);
                QLabel *tipo = new QLabel("Tipo: " + QString::fromStdString(searchVet[i]->getTipo()));
                tipo->setStyleSheet("font: italic 14px;");
                sensorLayout->addWidget(tipo);
                QLabel *descrizione = new QLabel("Descrizione: " + QString::fromStdString(searchVet[i]->getDescrizione()));
                descrizione->setStyleSheet("font: italic 14px;");
                sensorLayout->addWidget(descrizione);
                QPushButton *visualizza = new QPushButton("Visualizza " + QString::fromStdString(searchVet[i]->getNome()));
                visualizza->setObjectName("buttonVisualizza");
                visualizza->setStyleSheet("QPushButton#buttonVisualizza{border: 1px solid black; border-radius: 16px; padding: 8px;}"
                                          "QPushButton#buttonVisualizza:hover{background-color: lightgrey;}");
                connect(visualizza, &QPushButton::pressed, this, [this, searchVet, i](){ emit StartView(searchVet[i]); });
                sensorLayout->addWidget(visualizza);
                scrollayout->addWidget(sensorInfo, i, Qt::AlignTop);
            }
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
        QLabel* empty2;
        if(mod->getInsiemeSens().empty())
        {
            empty = new QLabel("La lista di sensori è vuota, si prega di aggiungerne di nuovi!");
            empty->setStyleSheet("font: bold 16px; color:red;");
            empty2 = new QLabel("Per aggiungere nuovi sensori premi i pulsanti 'Apri' o 'Crea' in alto!");
            empty2->setStyleSheet("font: bold 14px; color:black;");
            scrollayout->addWidget(empty, 0, Qt::AlignTop);
            scrollayout->addWidget(empty2, 1, Qt::AlignTop);
        }
        else
        {
            for(int i = 0; i < searchVet.size(); i++) {
                QString searchStr = QString::fromStdString(searchVet[i]->getNome());
                if((searchVet[i]->getNome() == search || searchStr.contains(QString::fromStdString(search), Qt::CaseInsensitive)))
                {
                    QWidget *sensorInfo = new QWidget();
                    sensorInfo->setObjectName("sensorInfo");
                    sensorInfo->setStyleSheet("QWidget#sensorInfo {border: 1px solid black;}");
                    sensorInfo->setFixedHeight(150);
                    QVBoxLayout *sensorLayout = new QVBoxLayout();
                    sensorLayout->setContentsMargins(10, 10, 10, 10);
                    sensorInfo->setLayout(sensorLayout);
                    QLabel *nome = new QLabel("Nome: " + QString::fromStdString(searchVet[i]->getNome()));
                    nome->setStyleSheet("font: bold 14px;");
                    sensorLayout->addWidget(nome);
                    QLabel *tipo = new QLabel("Tipo: " + QString::fromStdString(searchVet[i]->getTipo()));
                    tipo->setStyleSheet("font: italic 14px;");
                    sensorLayout->addWidget(tipo);
                    QLabel *descrizione = new QLabel("Descrizione: " + QString::fromStdString(searchVet[i]->getDescrizione()));
                    descrizione->setStyleSheet("font: italic 14px;");
                    sensorLayout->addWidget(descrizione);
                    QPushButton *visualizza = new QPushButton("Visualizza " + QString::fromStdString(searchVet[i]->getNome()));
                    visualizza->setObjectName("buttonVisualizza");
                    visualizza->setStyleSheet("QPushButton#buttonVisualizza{border: 1px solid black; border-radius: 16px; padding: 8px;}"
                                              "QPushButton#buttonVisualizza:hover{background-color: lightgrey;}");
                    connect(visualizza, &QPushButton::pressed, this, [this, searchVet, i](){ emit StartView(searchVet[i]); });
                    sensorLayout->addWidget(visualizza);
                    scrollayout->addWidget(sensorInfo, i, Qt::AlignTop);
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
