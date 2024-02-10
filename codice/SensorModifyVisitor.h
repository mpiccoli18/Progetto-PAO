#ifndef SENSORMODIFYVISITOR_H
#define SENSORMODIFYVISITOR_H

#include <QWidget>
#include "SensorVisitorInterface.h"

namespace sensore{

class SensorModifyVisitor: public sensore::SensorVisitorInterface {
private:
    QWidget* widget;

public:
    QWidget* getWidget();

    virtual void modSPneumatico(SensorePneumatico& sPneumatico);
    virtual void modSConsumo(SensoreConsumo& sConsumo);
    virtual void modSMotore(SensoreMotore& sMotore);
    virtual void modSBatteria(SensoreBatteria& sBatteria);
    virtual void modSGas(SensoreGas& sGas);

};

}

#endif // SENSORMODIFYVISITOR_H
