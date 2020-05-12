#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

//Protobuf headers
#include "protobuf/controls.pb.h"
#include "protobuf/sensors.pb.h"

//Peripheral controller header
#include "modules/peripheralcontroller.h"

//Network headers
#include "network/networkcontroller.h"


#include "timer/cppTimer/CppTimerCallback.h"

/*!
    \brief Класс логики управления роботом

    Данный класс реализует логику управления роботом.
*/
class LogicController: public CppTimerCallback::Runnable
{
    // Server settings
    std::string host = "10.11.11.11";
    int port = 7777;

    AmurSensors *sensors;
    AmurControls *controls;

    PeripheralController *periphery;
    NetworkController *network;

    CppTimerCallback logicTimer;

    void initTimer();
    void run();
public:
    LogicController();
    ~LogicController();

    void connectToServer(std::string host, unsigned int port);
    void connectToServer();

    void recvBuffer();
    void sendBuffer();

    void peripheryUpdate();
};

#endif // LOGICCONTROLLER_H
