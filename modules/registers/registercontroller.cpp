#include "registercontroller.h"

RegisterController::RegisterController
    (int dataPinHC595, int clkPinHC595, int latchPinHC595, int notResetPinHC595, int notEnablePinHC595,
     int dataPinHC165, int loadLatchPinHC165, int clkPinHC165, int clkInhibitePinHC165)
{
    outputRegister = new HC595(dataPinHC595, clkPinHC595, latchPinHC595, notResetPinHC595, notEnablePinHC595);
    inputRegister = new HC165(dataPinHC165, loadLatchPinHC165, clkPinHC165, clkInhibitePinHC165);
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
