#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include "protobuf/control.pb.h"
#include "protobuf/sensors.pb.h"

#include "tcp/tcpclient.h"
//#include "tcp/tcpserver.h" //Not used, only client mode

class NetworkController
{
    std::string serverHost;
    unsigned int serverPort;

    AmurSensors *sensorsPeri;
    AmurControls *controlsPeri;

    std::string *serializedControls;
    std::string serializedSensors;

    TCPClient *client;
public:
    NetworkController(AmurControls *controls, AmurSensors *sensors, std::string serverHost, unsigned int serverPort);
    NetworkController(AmurControls *controls, AmurSensors *sensors);
    ~NetworkController();

    void connect(std::string host, unsigned int port);
    void connect();
    void disconnect();

    void sendData();
    void recvData();

    void setHost(const std::string &value);
    void setPort(unsigned int value);
};

#endif // NETWORKCONTROLLER_H
