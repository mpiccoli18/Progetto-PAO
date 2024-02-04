#include <string>
#include <vector>

#include "sensoreConsumo.h"
#include "sensore.h"

namespace sensore{
    SensoreConsumo::SensoreConsumo(const std::string n, const std::string t, const std::string d,
                                         const std::vector<double> v, const double vMin, const double vMax,
                                         const std::string tCarburante): Sensore(n, t, d, v, vMin, vMax), tipoCarburante(tCarburante) {}

    const std::string& SensoreConsumo::getTipoCarburante() const {return tipoCarburante;}

    void SensoreConsumo::setTipoCarburante(std::string tCarburante) { tipoCarburante = tCarburante;}
}
