#ifndef HC165_H
#define HC165_H

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
#else
    #include <iostream>
#endif

#include "modules/peripheralsettings.h"


#define PULSE_WIDTH_USEC   1 // задержка импульса при считывании данных (каждый бит)

class HC165
{
    HC165Pins registerPins;

    inline void pulse(int pin);
public:    
    HC165(HC165Pins pins);
    unsigned char readByte();
    void loadRegister();        
    void disableClock();
    void enableClock();
};

#endif // HC165_H
