#include "searchBarPanel.h"
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QScrollArea>
namespace sensore{
    searchBarPanel::searchBarPanel(std::vector<Sensore*> v, QWidget* parent): QWidget(parent), vettore(v){
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        // Campo di testo per la ricerca
        ricerca = new QLineEdit(this);
        layout->addWidget(ricerca);

        // Pulsante per confermare la ricerca
        QPushButton* searchButton = new QPushButton("Cerca", this);
        layout->addWidget(searchButton);
        visualizzazione = new QScrollArea();
        visualizzazione->setWidgetResizable(true);
        scrollVisua = new QWidget();
        scrollayout = new QVBoxLayout();
        scrollVisua->setLayout(scrollayout);
        visualizzazione->setWidget(scrollVisua);
        layout->addWidget(visualizzazione);
        QLabel* empty;
        if(this->getVettore().empty())
        {
            empty = new QLabel("La lista di sensori è vuota, si prega di aggiungerne di nuovi!");
            empty->setStyleSheet("font: bold 16px; color:red;");
            scrollayout->addWidget(empty, 0, Qt::AlignTop);
        }
        connect(searchButton, &QPushButton::pressed, this, &searchBarPanel::StartSearch);
        connect(this, &searchBarPanel::StartSearch, this, &searchBarPanel::Search);
    }

    std::vector<Sensore*> searchBarPanel::getVettore() const{
        std::vector<Sensore*> v;

        for(auto i = vettore.begin(); i != vettore.end(); i++)
        {
            v.push_back(*i);
        }
        return v;
    }

    void searchBarPanel::Search()
    {
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
        std::vector<Sensore*> searchVet = this->getVettore();
        if(searchVet.empty())
        {
            QWidget *sensorInfo = new QWidget();
            QVBoxLayout *sensorLayout = new QVBoxLayout();
            sensorInfo->setLayout(sensorLayout);
            QLabel *empty = new QLabel("La lista di sensori è vuota");
            QLabel *empty2 = new QLabel("Si prega di aggiungerne di nuovi!");
            empty->setStyleSheet("font: bold 16px; color:red;");
            empty2->setStyleSheet("font: bold 16px; color:red;");
            sensorLayout->addWidget(empty, 0, Qt::AlignTop);
            sensorLayout->addWidget(empty2, 0, Qt::AlignTop);
            searchLayout->addWidget(sensorInfo);
        }
        else
        {
            // Create a scroll area
            QScrollArea *scrollArea = new QScrollArea();
            scrollArea->setWidgetResizable(true); // Widget can resize inside scroll area
            QWidget *scrollWidget = new QWidget();
            QVBoxLayout *scrollLayout = new QVBoxLayout();
            scrollWidget->setLayout(scrollLayout);
            scrollArea->setWidget(scrollWidget);
            searchLayout->addWidget(scrollArea);
            bool trovato = false;
            for(int i = 0; i < searchVet.size(); i++) {
                QString searchStr = QString::fromStdString(searchVet[i]->getNome());
                if(searchVet[i]->getNome() == search || (searchStr.contains(QString::fromStdString(search), Qt::CaseInsensitive) && search != ""))
                {
                    QWidget *sensorInfo = new QWidget();
                    sensorInfo->setObjectName("sensorInfo");
                    sensorInfo->setStyleSheet("QWidget#sensorInfo {border-bottom: 1px solid black;}");
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
                    connect(visualizza, &QPushButton::pressed, this, [this, searchVet, i]() { emit StartView(searchVet[i]); });
                    sensorLayout->addWidget(visualizza);
                    scrollLayout->addWidget(sensorInfo);
                    trovato = true;
                }
            }
            if(trovato == false)
            {
                QWidget *sensorInfo = new QWidget();
                QVBoxLayout *sensorLayout = new QVBoxLayout();
                sensorInfo->setLayout(sensorLayout);
                QLabel *errore = new QLabel("La ricerca non ha prodotto risultati!");
                errore->setStyleSheet("font: bold 14px;");
                sensorLayout->addWidget(errore, 0, Qt::AlignTop);
                scrollLayout->addWidget(sensorInfo);
            }
        }
        this->layout()->addWidget(risultati);
    }
}
