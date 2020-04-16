TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    AmurClient.cpp \
    protobuf/control.pb.cc \
    protobuf/sensors.pb.cc \
    logiccontroller.cpp \
    modules/encoder/encoder.cpp \
    modules/interfaces/i2c/I2C.cpp \
    modules/interfaces/spi/SPI.cpp \
    modules/interfaces/uart/UART.cpp \
    modules/motor/VNH2SP30/vnh2sp30.cpp \
    modules/motor/motorcontroller.cpp \
    modules/peripheralcontroller.cpp \
    modules/pwm/pwmcontroller.cpp \
    modules/registers/hc165/hc165.cpp \
    modules/registers/hc595/hc595.cpp \
    modules/registers/registercontroller.cpp \
    network/bufferController.cpp \
    network/client.c \
    network/server.c \
    network/tcp/tcp.cpp

DISTFILES += \
    protobuf/control.proto \
    protobuf/sensors.proto \
    protobuf/rebuild.sh \
    README.md

HEADERS += \
    protobuf/control.pb.h \
    protobuf/sensors.pb.h \
    logiccontroller.h \
    modules/encoder/encoder.h \
    modules/interfaces/i2c/I2C.h \
    modules/interfaces/spi/SPI.h \
    modules/interfaces/uart/UART.h \
    modules/motor/VNH2SP30/vnh2sp30.h \
    modules/motor/motorcontroller.h \
    modules/peripheralcontroller.h \
    modules/pwm/pwmcontroller.h \
    modules/registers/hc165/hc165.h \
    modules/registers/hc595/hc595.h \
    modules/registers/registercontroller.h \
    network/bufferController.h \
    network/tcp/tcp.h
