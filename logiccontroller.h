#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include <iomanip>
#include <cstdlib>

// Controllers headers
#include "modules/peripheralcontroller.h"
#include "network/networkcontroller.h"
#include "configprocessor.h"

/*!
    \brief Класс логики управления роботом

    Данный класс реализует логику управления роботом.
*/
class LogicController
{
    const char *configName = "amur.cfg";
    ConfigProcessor *config;
    PeripheralController *periphery;
    NetworkController *network;

    // Server settings
    std::string address = "192.168.0.101:7777";

    AMUR::AmurSensors sensors;
    AMUR::AmurControls controls;
    AMUR::AmurControls controlsPrev;

    void printHeadInfo();

    void worker();
    bool workerStopped = false;

public:
    LogicController();
    ~LogicController();

    void connectToServer(std::string host, unsigned int port);
    void connectToServer();
};

#endif // LOGICCONTROLLER_H
