#include "logiccontroller.h"

LogicController::LogicController()
{
    controls = new AmurControls();
    sensors = new AmurSensors();

    periphery = new PeripheralController(controls, sensors);
    network = new NetworkController(controls, sensors, SERVER_HOSTNAME, SERVER_PORT);
}

LogicController::~LogicController()
{
    delete sensors;
    delete controls;

    delete periphery;
    delete network;
}

void LogicController::connectToServer(std::string host, unsigned int port)
{
    network->connect(host, port);
}

void LogicController::recvBuffer()
{
    network->recvBufferAsString();
}
void LogicController::sendBuffer()
{
    network->sendBufferAsString();
}
