#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

//Peripheral controller header
#include "modules/peripheralcontroller.h"

//Network headers
#include "network/networkcontroller.h"

/*!
    \brief Класс логики управления роботом

    Данный класс реализует логику управления роботом.
*/
class LogicController
{
    // Server settings
    std::string host = "127.0.0.1";//"192.168.43.218";
    int port = 7777;

    AMUR::AmurSensors *sensors;
    AMUR::AmurControls *controls;

    AMUR::AmurControls controlsPrev;

    PeripheralController *periphery;
    NetworkController *network;

    TimerCallback logicTimer;

    void worker();
    bool workerStopped = false;

public:
    LogicController();
    ~LogicController();

    void connectToServer(std::string host, unsigned int port);
    void connectToServer();
};

#endif // LOGICCONTROLLER_H
