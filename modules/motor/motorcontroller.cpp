#include "motorcontroller.h"

MotorController::MotorController()
{

}

void MotorController::setRelayLeft(int value)
{
    relayLeft = value;
}

void MotorController::setRelayRight(int value)
{
    relayRight = value;
}
