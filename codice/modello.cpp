#include "modello.h"
#include "SensorInfoVisitor.h"
#include <QFileDialog>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonArray>

namespace sensore{
    modello::modello(){};
    std::vector<sensore::Sensore*> modello::getInsiemeSens() const{
        std::vector<Sensore*> sens;
        if(!InsiemeSensori.empty())
        {
            for(int i = 0; i < InsiemeSensori.size(); i++)
            {
                sens.push_back(InsiemeSensori[i]);
            }
        }
        return sens;
    };

    void modello::aggiungiSens(Sensore* s){
        InsiemeSensori.push_back(s);
    };

    void modello::eliminaSens(std::vector<Sensore*>::iterator s){
        InsiemeSensori.erase(s);
    };
}
