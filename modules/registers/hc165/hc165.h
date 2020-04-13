#ifndef HC165_H
#define HC165_H

#include <wiringPi.h>
 
#define PULSE_WIDTH_USEC   1 // задержка импульса при считывании данных (каждый бит)

class HC165
{
    int data          = 0; // Connects to the Q7 pin the 165
    int loadLatch     = 0; // Connects to Parallel load(SH/LD) pin the 165
    int clk           = 0; // Connects to the Clock(CLK) pin the 165
    int clkInhibite   = 0; // Connects to Clock Enable(CLK INH) pin the 165
    
    BYTES_VAL_T pinValues; // текущее значение пинов 
    BYTES_VAL_T oldPinValues; // предыдущее значение пинов
    
    void pulse(int pin);
public:    
    HC165(int dataPin, int loadLatchPin, int clkPin, int clkInhibitePin);
    unsigned char returnByte();        
    void loadRegister();        
    void disableClock();
    void enableClock();
};

#endif // HC165_H
