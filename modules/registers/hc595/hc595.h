#ifndef HC595_H
#define HC595_H

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
#endif

#include <iostream> // for debugging

#include "modules/peripheralsettings.h"

class HC595
{
    HC595Pins registerPins;
    
    inline void pulse(int pin);
public:
    HC595(HC595Pins pins);
    void writeByte(unsigned char byte);
    void latchSignal();
    void enable();
    void disable();
    void reset();
};

#endif // HC595_H
