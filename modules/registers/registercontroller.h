#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include "hc595/hc595.h"
#include "hc165/hc165.h"

#include "modules/peripheralsettings.h"

class RegisterController
{
    HC595 *outputRegister;
    HC165 *inputRegister;

public:
    RegisterController(HC595Pins outputPins, HC165Pins inputPins);
    ~RegisterController();

    void writeByte(unsigned char writingByte);
    unsigned char readByte();

    void refreshInputData();
    void refreshOutputData();

    void enableRegisters();
    void disableRegisters();
};

#endif // REGISTERCONTROLLER_H
