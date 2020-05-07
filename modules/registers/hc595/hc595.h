#ifndef HC595_H
#define HC595_H

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
#endif

#include <iostream> // for debugging

class HC595
{
    int data;       // Connects to data pin the 595
    int clk;        // Connects to clock pin the 595
    int latch;      // Connects to latch pin the 595
    int notReset;   // Connects to notReset pin the 595
    int notEnable;  // Connects to notEnable pin the 595
    
    inline void pulse(int pin);
public:
    HC595(int dataPin, int clkPin, int latchPin, int notResetPin, int notEnablePin);
    void writeByte(unsigned char byte);
    void latchSignal();
    void enable();
    void disable();
    void reset();
};

#endif // HC595_H
