#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

//Protobuf headers
#include "protobuf/controls.pb.h"
#include "protobuf/sensors.pb.h"

//Peripheral controller header
#include "modules/peripheralcontroller.h"

//Network headers
#include "network/networkcontroller.h"

// Server settings
#define SERVER_HOSTNAME "10.0.0.10"
#define SERVER_PORT 420

class LogicController
{
    AmurSensors *sensors;
    AmurControls *controls;

    PeripheralController *periphery;
    NetworkController *network;
public:
    LogicController();
    ~LogicController();

    void writeToPeriphery();
    void readFromPeriphery();

    void connectToServer(std::string host, unsigned int port);

    void recvBuffer();
    void sendBuffer();
};

#endif // LOGICCONTROLLER_H
