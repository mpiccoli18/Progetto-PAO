TEMPLATE = app
TARGET = progettoPAO
INCLUDEPATH += .
QT += widgets

SOURCES += \
    Info.cpp \
    SensorInfoVisitor.cpp \
    main.cpp \
    mainwindow.cpp \
    sensore.cpp \
    sensoreBatteria.cpp \
    sensoreConsumo.cpp \
    sensoreGas.cpp \
    sensoreMotore.cpp \
    sensorePneumatico.cpp

HEADERS += \
    Info.h \
    SensorInfoVisitor.h \
    SensorVisitorInterface.h \
    mainwindow.h \
    sensore.h \
    sensoreBatteria.h \
    sensoreConsumo.h \
    sensoreGas.h \
    sensoreMotore.h \
    sensorePneumatico.h
