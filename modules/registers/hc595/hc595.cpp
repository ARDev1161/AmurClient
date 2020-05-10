#include "hc595.h"
 
HC595::HC595(HC595Pins pins):
registerPins(pins)
{
#if __has_include(<wiringPi.h>)
    pinMode( registerPins.dataPin, OUTPUT);
    pinMode( registerPins.latchClkPin, OUTPUT);
    pinMode( registerPins.clkPin, OUTPUT);
    pinMode( registerPins.nResetPin, OUTPUT);
    pinMode( registerPins.nEnablePin, OUTPUT);

    digitalWrite( registerPins.dataPin, 0);
    digitalWrite( registerPins.latchClkPin, 0);
    digitalWrite( registerPins.clkPin, 0);
    digitalWrite( registerPins.nResetPin, 1);
    digitalWrite( registerPins.nEnablePin, 0);
#endif
}

inline void HC595::pulse(int pin)
{
#if __has_include(<wiringPi.h>)
    digitalWrite(pin, 0);
    digitalWrite(pin, 1);
#else
    std::cout << "HC595 Pulse on " << pin << std::endl;
#endif
}
 
void HC595::writeByte(unsigned char byte)
{
    int i; 
    for(i=0;i<8;i++){
    #if __has_include(<wiringPi.h>)
        digitalWrite( registerPins.dataPin, ((byte & (0x80 >> i)) > 0));
        pulse( registerPins.clkPin );
    #else
        std::cout << "HC595 Write byte -  " << byte << std::endl;
    #endif
    }
} 
 
void HC595::latchSignal()
{
    pulse( registerPins.latchClkPin );
}

void HC595::reset()
{
    pulse( registerPins.nResetPin );
}

void HC595::enable()
{
#if __has_include(<wiringPi.h>)
    digitalWrite( registerPins.nEnablePin , 0);
#else
    std::cout << "HC595 enable" << std::endl;
#endif
}

void HC595::disable()
{
#if __has_include(<wiringPi.h>)
    digitalWrite(  registerPins.nEnablePin , 1);
#else
    std::cout << "HC595 disable" << std::endl;
#endif
}
