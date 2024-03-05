#include <string>
#include <vector>
#include "sensore.h"

namespace sensore{

    Sensore::Sensore(
        const std::string n,
        const std::string t,
        const std::string d,
        const std::vector<double> v,
        const double vMin,
        const double vMax
    ) : nome(n), tipo(t), descrizione(d), valori(v), min(vMin), max(vMax) {}

    const std::string& Sensore::getNome() const {return nome;}
    const std::string& Sensore::getTipo() const {return tipo;}
    const std::string& Sensore::getDescrizione() const {return descrizione;}
    std::vector<double> Sensore::getValori() const{
        std::vector<double> v2;
        for(auto i = valori.begin(); i != valori.end(); i++)
        {
            v2.push_back(*i);
        }
        return v2;
    }
    double Sensore::getMin() const {return min;}
    double Sensore::getMax() const {return max;}

    void Sensore::setNome(std::string n) { nome = n; }
    void Sensore::setTipo(std::string t) { tipo = t; }
    void Sensore::setDescrizione(std::string d) { descrizione = d; }
    void Sensore::setMin(double vMin) { min = vMin; }
    void Sensore::setMax(double vMax) { max = vMax; }
    void Sensore::setValori(std::vector<double> v) {
        valori.clear();
        for(auto i = v.begin(); i != v.end(); i++)
        {
            valori.push_back(*i);
        }
    }
}
