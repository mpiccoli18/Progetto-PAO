#ifndef SEARCHBARPANEL_H
#define SEARCHBARPANEL_H

#include <vector>
#include <QWidget>
#include <QScrollArea>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include "sensore.h"
#include "modello.h"

namespace sensore{
    class searchBarPanel: public QWidget{
            Q_OBJECT
        private:
            QLineEdit *ricerca;
            QWidget *risultati = nullptr;
            QScrollArea* visualizzazione;
            QVBoxLayout* layoutV;
            QVBoxLayout* scrollayout;
            QWidget* scrollVisua;
            modello* mod;
        public:
            searchBarPanel(modello* m, QWidget *parent = nullptr);

        public slots:
            void Search();

        signals:
            void StartSearch();
            void StartView(sensore::Sensore* sensore);
    };
}

#endif // SEARCHBARPANEL_H
