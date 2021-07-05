#include <iostream>
#include <vector>
#include "hc595.h"

// Use this test for hardware debugging with debug motor board

int main(int argc, char *argv[])
{
    unsigned char wbyte = 0x00;
    std::vector<std::string> cmdLineArgs(argv, argv+argc);

    for(auto& arg : cmdLineArgs)
    {
        if(arg == "1" || arg == "-b")
        {
	    wbyte = 0xFF;
            std::cout << "Setting 0xFF\n";
        }
        else if(arg == "whatever")
        {
            std::cout << "whatever?!\n";
        }
    }

    int code;
#if __has_include(<pigpio.h>)
    if ( (code = gpioInitialise()) < 0 )
    {
    std::cerr << "piGPIO not initialized!!!" << std::endl << "code: " << code << std::endl;
	return 0;
    }

    std::cout << "Byte: " << wbyte << std::endl;
    HC595 *registr = new HC595();

    registr->writeByte(wbyte);
    registr->writeByte(wbyte);
    registr->latchSignal();

    gpioTerminate();
#endif
    return 0;
}

