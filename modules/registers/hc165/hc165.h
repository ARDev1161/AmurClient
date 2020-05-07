#ifndef HC165_H
#define HC165_H

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
#else
    #include <iostream>
#endif
 


#define PULSE_WIDTH_USEC   1 // задержка импульса при считывании данных (каждый бит)

class HC165
{
    int data;        // Connects to the Q7 pin the 165
    int loadLatch;   // Connects to Parallel load(SH/LD) pin the 165
    int clk;         // Connects to the Clock(CLK) pin the 165
    int clkInhibite; // Connects to Clock Enable(CLK INH) pin the 165

    inline void pulse(int pin);
public:    
    HC165(int dataPin, int loadLatchPin, int clkPin, int clkInhibitePin);
    unsigned char readByte();
    void loadRegister();        
    void disableClock();
    void enableClock();
};

#endif // HC165_H
