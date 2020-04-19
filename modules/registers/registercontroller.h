#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include "hc595/hc595.h"
#include "hc165/hc165.h"

class RegisterController
{
    HC595 *outputRegister;
    HC165 *inputRegister;

public:
    RegisterController(int dataPinHC595, int clkPinHC595, int latchPinHC595, int notResetPinHC595, int notEnablePinHC595,
                       int dataPinHC165, int loadLatchPinHC165, int clkPinHC165, int clkInhibitePinHC165);
    ~RegisterController();

    void writeByte(unsigned char writingByte);
    unsigned char readByte();

    void refreshInputData();
    void refreshOutputData();

    void enableRegisters();
    void disableRegisters();
};

#endif // REGISTERCONTROLLER_H
