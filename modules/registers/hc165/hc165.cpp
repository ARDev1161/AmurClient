#include "hc165.h"
 
HC165::HC165(int dataPin, int loadLatchPin, int clkPin, int clkInhibitePin):
data(dataPin), loadLatch(loadLatchPin), clk(clkPin), clkInhibite(clkInhibitePin)
{
    pinMode(data, INPUT);
    
    pinMode(loadLatch, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(clkInhibite, OUTPUT);
    
    digitalWrite(loadLatch, 0);
    digitalWrite(clk, 0);
    digitalWrite(clkInhibite, 0);
}

void HC165::pulse(int pin)
{
    digitalWrite(pin, 0);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(pin, 1);
}

void HC165::disableClock()
{
    digitalWrite(clkInhibite, 1);
}

void HC165::enableClock()
{    
    digitalWrite(clkInhibite, 0);
}

void HC165::loadRegister()
{
    // load
    disableClock();
    
    pulse(loadLatch);
    digitalWrite(loadLatch, 0);
    
    enableClock();
}

unsigned char HC165::readByte()
{
    unsigned char byte = 0;
    
    // shiftin
    for(int i = 0; i < 8; i++)
    {
        byte |= (digitalRead(data) << (7 - i));
        pulse(clk);
    }

    return(byte);
}
