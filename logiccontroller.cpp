#include "logiccontroller.h"

LogicController::LogicController()
{
    controls = new AmurControls();
    sensors = new AmurSensors();
    periphery = new PeripheralController(controls, sensors);
    network = new NetworkController(controls, sensors, host, port);

    initTimer();
}

LogicController::~LogicController()
{
    delete sensors;
    delete controls;

    delete periphery;
    delete network;
}

void LogicController::initTimer()
{
    logicTimer.registerEventRunnable(*this);
    logicTimer.start(42000000); // 42 milliseconds

    std::this_thread::sleep_for(std::chrono::seconds(1));// Wait 1 second
}

void LogicController::run()
{
    if(network->checkAlive()){
        sendBuffer();
        recvBuffer();

        peripheryUpdate();
    }
    else{
        connectToServer();
    }
}

void LogicController::connectToServer(std::string host, unsigned int port)
{
    this->host = host;
    this->port =port;

    network->connect(host, port);
}
void LogicController::connectToServer()
{
    network->connect();
}

void LogicController::recvBuffer()
{
    network->recvBufferAsString();
}
void LogicController::sendBuffer()
{
    network->sendBufferAsString();
}

void LogicController::peripheryUpdate()
{
    periphery->updateData();
}
