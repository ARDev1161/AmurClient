#ifndef HC595_H
#define HC595_H

#include <iostream>

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#endif

#include "../registerssettings.h"

/*!
    \brief Класс работы с регистром 74HC595

    Данный класс позволяет записывать данные в регистр из байта входящих данных, выключать и включать его.
*/

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
