TEMPLATE = app
TARGET = progettoPAO
INCLUDEPATH += .
QT += widgets

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    sensore.cpp \
    sensoreConsumo.cpp \
    sensorePneumatico.cpp

HEADERS += \
    SensorVisitorInterface.h \
    mainwindow.h \
    sensore.h \
    sensoreConsumo.h \
    sensorePneumatico.h
