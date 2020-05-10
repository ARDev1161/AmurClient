#include "registercontroller.h"

RegisterController::RegisterController
    (HC595Pins outputPins, HC165Pins inputPins)
{
    outputRegister = new HC595(outputPins);
    inputRegister = new HC165(inputPins);
}

RegisterController::~RegisterController()
{
    delete outputRegister;
    delete inputRegister;
}

void RegisterController::writeByte(unsigned char writingByte)
{
    outputRegister->writeByte(writingByte);
}

unsigned char RegisterController::readByte()
{
    return inputRegister->readByte();
}

void RegisterController::refreshOutputData()
{
    outputRegister->latchSignal();
}

void RegisterController::refreshInputData()
{
    inputRegister->loadRegister();
}

void RegisterController::enableRegisters()
{
    outputRegister->enable();
    inputRegister->enableClock();
}

void RegisterController::disableRegisters()
{
    outputRegister->disable();
    inputRegister->disableClock();
}
