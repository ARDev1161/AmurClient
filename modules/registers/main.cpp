#include <iostream>

#include "registercontroller.h"
#include "peripheralsettings.h"

using namespace std;

int main()
{
    PeripheralSettings settings;

    RegisterController *registers;
    registers = new RegisterController(settings.outputRegisters,
                                       settings.inputRegisters);

    unsigned char byte = 0x00;

    registers->writeByte(byte);

    cout << "Hello World!" << endl;
    return 0;
}
