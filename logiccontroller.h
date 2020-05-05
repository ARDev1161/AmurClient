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
#define SERVER_HOSTNAME "10.11.11.11"
#define SERVER_PORT 7777

class LogicController
{
    AmurSensors *sensors;
    AmurControls *controls;

    PeripheralController *periphery;
    NetworkController *network;
public:
    LogicController();
    ~LogicController();

    void connectToServer(std::string host, unsigned int port);

    void recvBuffer();
    void sendBuffer();
};

#endif // LOGICCONTROLLER_H
