#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

#include <iomanip>
#include <cstdlib>

// Controllers headers
#include "modules/peripheralcontroller.h"
#include "network/networkcontroller.h"

#include <libconfig.h++>

#if ((LIBCONFIGXX_VER_MAJOR == 1) && (LIBCONFIGXX_VER_MINOR >= 4))
    // использовать возможности, представленные в libconfig 1.4 и новее
#endif

/*!
    \brief Класс логики управления роботом

    Данный класс реализует логику управления роботом.
*/
class LogicController
{
    // libconfig settings
    const char *configName = "amur.cfg";
    libconfig::Config config;

    // Server settings
    std::string address = "176.193.245.203:7777";

    AMUR::AmurSensors *sensors;
    AMUR::AmurControls *controls;

    AMUR::AmurControls controlsPrev;

    PeripheralController *periphery;
    NetworkController *network;

    void worker();
    bool workerStopped = false;

public:
    LogicController();
    ~LogicController();

    void connectToServer(std::string host, unsigned int port);
    void connectToServer();

    int setOptionsConfig (const char *configName);
    int readConfig (const char *configName);
    int writeConfig(const char *configName);

    int configSearch(const char *settingName);

    const char *getConfigFilename() const;
    void setConfigFilename(const char *newConfigName);
};

#endif // LOGICCONTROLLER_H
