#include "logiccontroller.h"

LogicController::LogicController()
{
    controls = new AmurControls();
    sensors = new AmurSensors();

    periphery = new PeripheralController(controls, sensors);
    network = new NetworkController();
}

LogicController::~LogicController()
{
    delete sensors;
    delete controls;

    delete periphery;
    delete network;
}

void LogicController::writeToPeriphery()
{

}

void LogicController::readFromPeriphery()
{

}
