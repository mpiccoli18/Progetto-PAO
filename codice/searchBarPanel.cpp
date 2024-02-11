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
        QLineEdit* searchLineEdit = new QLineEdit(this);
        layout->addWidget(searchLineEdit);

        // Pulsante per confermare la ricerca
        QPushButton* searchButton = new QPushButton("Cerca", this);
        layout->addWidget(searchButton);

    }
}
