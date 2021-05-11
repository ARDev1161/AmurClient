#ifndef HC165_H
#define HC165_H

#include <iostream>

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#endif

#include "../registerssettings.h"

/*!
    \brief Класс работы с регистром 74HC165

    Данный класс позволяет считывать данные из регистра в байт данных, выключать и включать его.
*/

class HC165
{
    RegisterSettings *settings;

    inline void pulse(int pin);
public:    
    HC165(RegisterSettings *settings);
    unsigned char readByte();
    void loadRegister();        
    void disableClock();
    void enableClock();
};

#endif // HC165_H
