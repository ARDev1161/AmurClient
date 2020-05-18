#include "hc165.h"
 
/*!
Создаёт экземпляр класса для считывания из регистра.
\param[in] pins Структура описывающая пины Raspberry Pi для подключения регистра в нотации GPIO
*/
HC165::HC165(HC165Pins pins):
registerPins(pins)
{
#if __has_include(<wiringPi.h>)
    pinMode( registerPins.dataPin , INPUT);

    pinMode( registerPins.loadPin , OUTPUT);
    pinMode( registerPins.clkPin , OUTPUT);
    pinMode( registerPins.clkInhibitePin , OUTPUT);

    digitalWrite( registerPins.loadPin , 0);
    digitalWrite( registerPins.clkPin , 0);
    digitalWrite( registerPins.clkInhibitePin , 0);
#endif
}

/*!
Подаёт импульс на указанный пин управления регистра.
\param[in] pin Пин GPIO для управления регистром
*/
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

/*!
Выключает регистр.
*/
void HC165::disableClock()
{
#if __has_include(<wiringPi.h>)
    digitalWrite( registerPins.clkInhibitePin , 1);
#else
    std::cout << "HC165 disable" << std::endl;
#endif
}

/*!
Включает регистр.
*/
void HC165::enableClock()
{    
#if __has_include(<wiringPi.h>)
    digitalWrite( registerPins.clkInhibitePin , 0);
#else
    std::cout << "HC165 enable" << std::endl;
#endif
}

/*!
Записывает данные на выводах регистра в память регистра.
*/
void HC165::loadRegister()
{
    // load
#if __has_include(<wiringPi.h>)
    disableClock();

    pulse( registerPins.loadPin );
    digitalWrite( registerPins.loadPin , 0);

    enableClock();
#endif
}

/*!
Считывает байт данных из регистра.
\return byte Байт считанных данных
*/
unsigned char HC165::readByte()
{
    unsigned char byte = 0;

#if __has_include(<wiringPi.h>)
    // shiftin
    for(int i = 0; i < 8; i++)
    {
        byte |= (digitalRead( registerPins.dataPin ) << (7 - i));
        pulse( registerPins.clkPin );
    }
#endif

    return(byte);
}
