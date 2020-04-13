#include "logiccontroller.h"

LogicController::LogicController()
{
    controls = new AmurControls();
    sensors = new AmurSensors();

    periphery = new PeripheralController(controls, sensors);
}

void LogicController::writeToPeriphery()
{

}

void LogicController::readFromPeriphery()
{

}
