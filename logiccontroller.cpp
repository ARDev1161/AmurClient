#include "logiccontroller.h"

LogicController::LogicController()
{
    controls = new AmurControls();
    sensors = new AmurSensors();

    periphery = new PeripheralController(controls, sensors);
}

LogicController::~LogicController()
{
    delete sensors;
    delete controls;

    delete periphery;
}

void LogicController::writeToPeriphery()
{

}

void LogicController::readFromPeriphery()
{

}
