#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

//Peripheral controller header
#include "modules/peripheralcontroller.h"

//Network headers
#include "network/networkcontroller.h"

#include "timer/TimerCallback.h"

/*!
    \brief Класс логики управления роботом

    Данный класс реализует логику управления роботом.
*/
class LogicController: public TimerCallback::Runnable
{
    // Server settings
//    std::string host = "11.11.11.11";
    std::string host = "127.0.0.1";
    int port = 7777;

    AMUR::AmurSensors *sensors;
    AMUR::AmurControls *controls;

    AMUR::AmurControls controlsPrev;
    std::string sensorsPrev;

    PeripheralController *periphery;
    NetworkController *network;

    TimerCallback logicTimer;

    void initTimer();
    void run();

public:
    LogicController();
    ~LogicController();

    void connectToServer(std::string host, unsigned int port);
    void connectToServer();

    void peripheryUpdate();
};

#endif // LOGICCONTROLLER_H
