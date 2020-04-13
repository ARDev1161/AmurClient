#include "hc595.h"
 
HC595::HC595(int dataPin, int clkPin, int latchPin, int notResetPin, int notEnablePin):
data(dataPin), clk(clkPin), latch(latchPin), notReset(notResetPin), notEnable(notEnablePin)
{
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
}

void HC595::pulse(int pin)
{
    digitalWrite(pin, 0);
    digitalWrite(pin, 1);
}
 
void HC595::writeByte(unsigned char byte)
{
    int i; 
    for(i=0;i<8;i++)
	{
        digitalWrite(data, ((byte & (0x80 >> i)) > 0));
        pulse(clk);
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
    digitalWrite(notEnable, 0);
}

void HC595::disable()
{
    digitalWrite(notEnable, 1);
}
