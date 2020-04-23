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
    delete serializedControls;
    delete client;
}

void NetworkController::connect(std::string host, unsigned int port)
{
    client->connect(host, port);
}
void NetworkController::connect()
{
    client->connect(serverHost, serverPort);
}
void NetworkController::disconnect()
{
    client->disconnect();
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
