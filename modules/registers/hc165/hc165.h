#ifndef HC165_H
#define HC165_H

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
#else
    #include <iostream>
#endif

#include "../../peripheralsettings.h"


#define PULSE_WIDTH_USEC   1 // задержка импульса при считывании данных (каждый бит)

/*!
    \brief Класс работы с регистром 74HC165

    Данный класс позволяет считывать данные из регистра в байт данных, выключать и включать его.
*/

class HC165
{
    HC165Pins registerPins;

    inline void pulse(int pin);
public:    
    HC165(HC165Pins pins);
    unsigned char readByte();
    void loadRegister();        
    void disableClock();
    void enableClock();
};

#endif // HC165_H
