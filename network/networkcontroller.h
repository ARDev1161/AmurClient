#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include "protobuf/controls.pb.h"
#include "protobuf/sensors.pb.h"

#include "tcp/tcpclient.h"
//#include "tcp/tcpserver.h" //Not used, only client mode

/*!
    \brief Класс контроллера работы с сетью

    Данный класс инкапсулирует логику работы с сетью.
*/
class NetworkController
{
    std::string serverHost = "";
    unsigned int serverPort = 0;

    AmurSensors *sensorsPeri;
    AmurControls *controlsPeri;

    std::string serializedControls;
    std::string *serializedSensors;

    TCPClient *client;
public:
    NetworkController(AmurControls *controls, AmurSensors *sensors, std::string serverHost, unsigned int serverPort);
    NetworkController(AmurControls *controls, AmurSensors *sensors);
    ~NetworkController();

    bool connect(std::string host, unsigned int port);
    bool connect();
    void disconnect();

    bool checkAlive();

    void sendBufferAsString();
    void recvBufferAsString();    

    void setHost(const std::string &value);
    void setPort(unsigned int value);
};

#endif // NETWORKCONTROLLER_H
