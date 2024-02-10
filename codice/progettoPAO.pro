TEMPLATE = app
TARGET = progettoPAO
INCLUDEPATH += .
QT += widgets
QT += charts

SOURCES += \
    Info.cpp \
    SensorInfoVisitor.cpp \
    SensorModifyVisitor.cpp \
    homePanel.cpp \
    main.cpp \
    mainwindow.cpp \
    sensorPanel.cpp \
    sensore.cpp \
    sensoreBatteria.cpp \
    sensoreConsumo.cpp \
    sensoreGas.cpp \
    sensoreMotore.cpp \
    sensorePneumatico.cpp

HEADERS += \
    Info.h \
    SensorInfoVisitor.h \
    SensorModifyVisitor.h \
    SensorVisitorInterface.h \
    homePanel.h \
    mainwindow.h \
    sensorPanel.h \
    sensore.h \
    sensoreBatteria.h \
    sensoreConsumo.h \
    sensoreGas.h \
    sensoreMotore.h \
    sensorePneumatico.h
