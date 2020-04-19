TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    AmurClient.cpp \
    network/networkcontroller.cpp \
    network/tcp/tcpclient.cpp \
    network/tcp/tcpserver.cpp \
    protobuf/control.pb.cc \
    protobuf/sensors.pb.cc \
    logiccontroller.cpp \
    modules/interfaces/i2c/I2C.cpp \
    modules/interfaces/spi/SPI.cpp \
    modules/interfaces/uart/UART.cpp \
    modules/peripheralcontroller.cpp \
    modules/pwm/pwmcontroller.cpp \
    modules/registers/hc165/hc165.cpp \
    modules/registers/hc595/hc595.cpp \
    modules/registers/registercontroller.cpp

DISTFILES += \
    protobuf/control.proto \
    protobuf/sensors.proto \
    protobuf/rebuild.sh \
    README.md

HEADERS += \
    network/networkcontroller.h \
    network/tcp/tcpclient.h \
    network/tcp/tcpserver.h \
    protobuf/control.pb.h \
    protobuf/sensors.pb.h \
    logiccontroller.h \
    modules/interfaces/i2c/I2C.h \
    modules/interfaces/spi/SPI.h \
    modules/interfaces/uart/UART.h \
    modules/peripheralcontroller.h \
    modules/pwm/pwmcontroller.h \
    modules/registers/hc165/hc165.h \
    modules/registers/hc595/hc595.h \
    modules/registers/registercontroller.h
