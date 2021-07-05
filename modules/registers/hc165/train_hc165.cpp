#include <iostream>
#include <unistd.h>
#include "hc165.h"
#include "../registerssettings.h"

#define FREQ_PIN 10

int main()
{
    unsigned char oldF = 0;
    unsigned char oldS = 0;

    unsigned char curF;
    unsigned char curS;

    RegisterSettings settings;
    HC165 *reg = new HC165(&settings);

    int code;
#if __has_include(<pigpio.h>)
    if ( (code = gpioInitialise()) < 0 )
    {
        std::cerr << "piGPIO not initialized!!!" << std::endl << "code: " << code << std::endl;
        return 0;
    }


    while(true)
    {
        reg->loadRegister();

	curF = (int)reg->readByte();
        curS = (int)reg->readByte();

        if(oldF != curF)
	{
	    std::cout << "First byte: " << (int)curF << std::endl;
	    oldF = curF;
	}
	if(oldS != curS)
	{
	    std::cout << "Second byte: " << (int)curS << std::endl;
	    oldS = curS;
	}
        usleep(10000);
    }

    gpioTerminate();
#endif

    return 0;
}

