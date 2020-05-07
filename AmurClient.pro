TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -L$$LIBS_PATH /
LIBS += -lprotobuf \
        -lpthread \
        -lrt

SOURCES += \
    AmurClient.cpp \
    modules/interfaces/i2c/i2c.cpp \
    modules/interfaces/spi/spi.cpp \
    modules/interfaces/uart/uart.cpp \
    network/networkcontroller.cpp \
    network/tcp/tcpclient.cpp \
    network/tcp/tcpserver.cpp \
    logiccontroller.cpp \
    modules/peripheralcontroller.cpp \
    modules/pwm/pwmcontroller.cpp \
    modules/registers/hc165/hc165.cpp \
    modules/registers/hc595/hc595.cpp \
    modules/registers/registercontroller.cpp \
    protobuf/controls.pb.cc \
    protobuf/sensors.pb.cc \
    timer/cppTimer/CppTimer.cpp

DISTFILES += \
    protobuf/controls.proto \
    protobuf/rebuild.sh \
    README.md \
    protobuf/sensors.proto

HEADERS += \
    modules/interfaces/i2c/i2c.h \
    modules/interfaces/spi/spi.h \
    modules/interfaces/uart/uart.h \
    network/networkcontroller.h \
    network/tcp/tcpclient.h \
    network/tcp/tcpserver.h \
    protobuf/buffers.pb.h \
    logiccontroller.h \
    modules/peripheralcontroller.h \
    modules/pwm/pwmcontroller.h \
    modules/registers/hc165/hc165.h \
    modules/registers/hc595/hc595.h \
    modules/registers/registercontroller.h \
    protobuf/controls.pb.h \
    protobuf/sensors.pb.h \
    timer/cppTimer/CppTimer.h \
    timer/cppTimer/CppTimerCallback.h
