#ifndef SEARCHBARPANEL_H
#define SEARCHBARPANEL_H

#include<vector>
#include<QWidget>
#include<QScrollArea>
#include<QLineEdit>
#include<QVBoxLayout>
#include"sensore.h"

namespace sensore{
    class searchBarPanel: public QWidget{
            Q_OBJECT
        private:
            std::vector<Sensore*> vettore;
            QLineEdit *ricerca;
            QWidget *risultati = nullptr;
            QScrollArea* visualizzazione;
            QVBoxLayout* layoutV;
            QVBoxLayout* scrollayout;
            QWidget* scrollVisua;
        public:
            searchBarPanel(const std::vector<Sensore*> v, QWidget *parent = nullptr);

            std::vector<Sensore*> getVettore() const;

            void setVettore(Sensore* s);

        public slots:
            void Search();

        signals:
            void StartSearch();
            void StartView(sensore::Sensore* sensore);
    };
}

#endif // SEARCHBARPANEL_H
