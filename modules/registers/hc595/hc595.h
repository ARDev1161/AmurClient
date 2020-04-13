#ifndef HC595_H
#define HC595_H

#include <wiringPi.h>

class HC595
{
    int data = 0;
    int clk = 0;
    int latch = 0;
    int notReset = 0; 
    int notEnable = 0;
    
    void pulse(int pin);
public:
    HC595(int dataPin, int clkPin, int latchPin, int notResetPin, int notEnablePin);
    void sendByte(unsigned char byte);
    void latchSignal();
    void enable();
    void disable();
    void reset();
};

#endif // HC595_H
