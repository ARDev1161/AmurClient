#include "networkcontroller.h"


NetworkController::NetworkController(AmurControls *controls, AmurSensors *sensors, std::string host, unsigned int port):
    serverHost(host), serverPort(port),
    sensorsPeri(sensors), controlsPeri(controls)
{
    serializedControls = new std::string();
    client = new TCPClient(serverHost, serverPort);
}

NetworkController::NetworkController(AmurControls *controls, AmurSensors *sensors):
    sensorsPeri(sensors), controlsPeri(controls)
{
    client = new TCPClient();
}

NetworkController::~NetworkController()
{
    disconnect();

    delete serializedControls;
    delete client;
}

bool NetworkController::connect(std::string host, unsigned int port)
{
    return client->connect(host, port);
}
bool  NetworkController::connect()
{
    bool res = false;
    if((serverPort > 0) && (serverHost !=""))
        res = client->connect(serverHost, serverPort);
    return res;
}
void NetworkController::disconnect()
{
    client->disconnect();
}

bool NetworkController::checkAlive()
{
    return client->checkAlive();
}

void NetworkController::sendBufferAsString()
{
    controlsPeri->SerializeToString(serializedControls);

    client->write(*serializedControls);
}
void NetworkController::recvBufferAsString()
{
    sensorsPeri->ParseFromString( client->read() );
}

void NetworkController::setHost(const std::string &value)
{
    serverHost = value;
}
void NetworkController::setPort(unsigned int value)
{
    serverPort = value;
}
