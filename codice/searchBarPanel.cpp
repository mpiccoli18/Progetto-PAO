#include "searchBarPanel.h"
#include<QVBoxLayout>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>

namespace sensore{
    searchBarPanel::searchBarPanel(std::vector<Sensore*> v, QWidget* parent): QWidget(parent),vectors(v){
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setAlignment(Qt::AlignLeft | Qt::AlignTop);

        // Campo di testo per la ricerca
        searchLineEdit = new QLineEdit(this);
        layout->addWidget(searchLineEdit);

        // Pulsante per confermare la ricerca
        QPushButton* searchButton = new QPushButton("Cerca", this);
        layout->addWidget(searchButton);

        connect(searchButton, &QPushButton::pressed, this, &searchBarPanel::StartSearch);
        connect(this, &searchBarPanel::StartSearch, this, &searchBarPanel::Search);
    }

    std::vector<Sensore*> searchBarPanel::getVectors() const{
        std::vector<Sensore*> vettore;

        for(auto i = vectors.begin(); i != vectors.end(); i++)
        {
            vettore.push_back(*i);
        }
        return vettore;
    }

    void searchBarPanel::Search()
    {
        if(searchResult)
        {
            this->layout()->removeWidget(searchResult);
            delete searchResult;
            searchResult = nullptr;
        }
        std::string search = (this->searchLineEdit->text()).toStdString();
        std::vector<Sensore*> searchVet = this->getVectors();
        if(searchVet.empty())
        {
            QLabel* empty = new QLabel("La lista di sensori è vuota, si prega di aggiungerne di nuovi!");
            this->layout()->addWidget(empty);
            qDebug() << "il vettore è vuoto!";
        }
        else
        {
            searchResult = new QWidget();
            QVBoxLayout *searchLayout = new QVBoxLayout();
            searchResult->setLayout(searchLayout);
            for(int i = 0; i < searchVet.size(); i++)
            {
                QString searchStr = QString::fromStdString(searchVet[i]->getName());
                if(searchVet[i]->getName() == search || (searchStr.contains(QString::fromStdString(search), Qt::CaseInsensitive) && search != ""))
                {
                    QWidget *sensorInfo = new QWidget();
                    sensorInfo->setObjectName("sensorInfo");
                    sensorInfo->setStyleSheet("QWidget#sensorInfo {border-bottom: 1px solid black;}");
                    QVBoxLayout *sensorLayout = new QVBoxLayout();
                    sensorInfo->setLayout(sensorLayout);
                    QLabel *nome = new QLabel("Nome: " + QString::fromStdString(searchVet[i]->getName()));
                    nome->setStyleSheet("font: bold 14px;");
                    sensorLayout->addWidget(nome);
                    QLabel *tipo = new QLabel("Tipo: " + QString::fromStdString(searchVet[i]->getType()));
                    sensorLayout->addWidget(tipo);
                    QLabel *descrizione = new QLabel("Descrizione: " + QString::fromStdString(searchVet[i]->getDescription()));
                    sensorLayout->addWidget(descrizione);
                    QPushButton *visualizza = new QPushButton("Visualizza " + QString::fromStdString(searchVet[i]->getName()));
                    sensorLayout->addWidget(visualizza);
                    searchLayout->addWidget(sensorInfo);
                }
            }
        }
        this->layout()->addWidget(searchResult);
    }
}
