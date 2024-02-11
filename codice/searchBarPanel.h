#ifndef SEARCHBARPANEL_H
#define SEARCHBARPANEL_H

#include<vector>
#include<QWidget>
#include"sensore.h"

namespace sensore{
    class searchBarPanel: public QWidget{
            Q_OBJECT
        private:
            std::vector<Sensore*> vectors;
        public:
            searchBarPanel(const std::vector<Sensore*> v, QWidget *parent = nullptr);

            std::vector<Sensore*> getVectors() const;

            void setVectors(Sensore* s);

        signals:

    };
}

#endif // SEARCHBARPANEL_H
