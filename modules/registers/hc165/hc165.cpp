#include "hc165.h"
 
HC165::HC165(int dataPin, int loadLatchPin, int clkPin, int clkInhibitePin):
data(dataPin), loadLatch(loadLatchPin), clk(clkPin), clkInhibite(clkInhibitePin)
{
#if __has_include(<wiringPi.h>)
    pinMode(data, INPUT);

    pinMode(loadLatch, OUTPUT);
    pinMode(clk, OUTPUT);
    pinMode(clkInhibite, OUTPUT);

    digitalWrite(loadLatch, 0);
    digitalWrite(clk, 0);
    digitalWrite(clkInhibite, 0);
#endif
}

inline void HC165::pulse(int pin)
{
#if __has_include(<wiringPi.h>)
    digitalWrite(pin, 0);
    delayMicroseconds(PULSE_WIDTH_USEC);
    digitalWrite(pin, 1);
#else
    std::cout << "HC165 Pulse in" << pin << std::endl;
#endif
}

void HC165::disableClock()
{
#if __has_include(<wiringPi.h>)
    digitalWrite(clkInhibite, 1);
#else
    std::cout << "HC165 disable" << std::endl;
#endif
}

void HC165::enableClock()
{    
#if __has_include(<wiringPi.h>)
    digitalWrite(clkInhibite, 0);
#else
    std::cout << "HC165 enable" << std::endl;
#endif
}

void HC165::loadRegister()
{
    // load
#if __has_include(<wiringPi.h>)
    disableClock();

    pulse(loadLatch);
    digitalWrite(loadLatch, 0);

    enableClock();
#else
    std::cout << "HC165 load" << std::endl;
#endif
}

unsigned char HC165::readByte()
{
    unsigned char byte = 0;

#if __has_include(<wiringPi.h>)
    // shiftin
    for(int i = 0; i < 8; i++)
    {
        byte |= (digitalRead(data) << (7 - i));
        pulse(clk);
    }
#else
    std::cout << "HC165 read - " << byte << std::endl;
#endif

    return(byte);
}
