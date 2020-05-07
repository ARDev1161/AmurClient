#include "hc595.h"
 
HC595::HC595(int dataPin, int clkPin, int latchPin, int notResetPin, int notEnablePin):
data(dataPin), clk(clkPin), latch(latchPin), notReset(notResetPin), notEnable(notEnablePin)
{
#if __has_include(<wiringPi.h>)
    pinMode(data, OUTPUT);
    pinMode(latch, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(notReset, OUTPUT);
    pinMode(notEnable, OUTPUT);

    digitalWrite(data, 0);
    digitalWrite(latch, 0);
    digitalWrite(clk, 0);
    digitalWrite(notReset, 1);
    digitalWrite(notEnable, 0);
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
        digitalWrite(data, ((byte & (0x80 >> i)) > 0));
        pulse(clk);
    #else
        std::cout << "HC595 Write byte -  " << byte << std::endl;
    #endif
    }
} 
 
void HC595::latchSignal()
{
    pulse(latch);
}

void HC595::reset()
{
    pulse(notReset);
}

void HC595::enable()
{
#if __has_include(<wiringPi.h>)
    digitalWrite(notEnable, 0);
#else
    std::cout << "HC595 enable" << std::endl;
#endif
}

void HC595::disable()
{
#if __has_include(<wiringPi.h>)
    digitalWrite(notEnable, 1);
#else
    std::cout << "HC595 disable" << std::endl;
#endif
}
