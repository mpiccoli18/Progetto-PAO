#ifndef SEARCHBARPANEL_H
#define SEARCHBARPANEL_H

#include<vector>
#include<QWidget>
#include<QLineEdit>
#include"sensore.h"

namespace sensore{
    class searchBarPanel: public QWidget{
            Q_OBJECT
        private:
            std::vector<Sensore*> vectors;
            QLineEdit *searchLineEdit;
            QWidget *searchResult = nullptr;
        public:
            searchBarPanel(const std::vector<Sensore*> v, QWidget *parent = nullptr);

            std::vector<Sensore*> getVectors() const;

            void setVectors(Sensore* s);

        public slots:
            void Search();

        signals:
            void StartSearch();
    };
}

#endif // SEARCHBARPANEL_H
