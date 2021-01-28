#include "hc165.h"
 
/*!
Создаёт экземпляр класса для считывания из регистра.
\param[in] pins Структура описывающая пины Raspberry Pi для подключения регистра в нотации GPIO
*/
HC165::HC165(HC165Pins pins):
registerPins(pins)
{
#if __has_include(<pigpio.h>)
    gpioSetMode( registerPins.dataPin , PI_INPUT);

    gpioSetMode( registerPins.loadPin , PI_OUTPUT);
    gpioSetMode( registerPins.clkPin , PI_OUTPUT);
    gpioSetMode( registerPins.clkInhibitePin , PI_OUTPUT);

    gpioWrite( registerPins.loadPin , 0);
    gpioWrite( registerPins.clkPin , 0);
    gpioWrite( registerPins.clkInhibitePin , 0);
#endif
}

/*!
Подаёт импульс на указанный пин управления регистра.
\param[in] pin Пин GPIO для управления регистром
*/
inline void HC165::pulse(int pin)
{
#if __has_include(<pigpio.h>)
    gpioWrite(pin, 0);
    gpioDelay(PULSE_WIDTH_USEC);
    gpioWrite(pin, 1);
#else
    std::cout << "HC165 Pulse in" << pin << std::endl;
#endif
}

/*!
Выключает регистр.
*/
void HC165::disableClock()
{
#if __has_include(<pigpio.h>)

#else
    std::cout << "HC165 disable" << std::endl;
#endif
}

/*!
Включает регистр.
*/
void HC165::enableClock()
{
#if __has_include(<pigpio.h>)
    gpioWrite( registerPins.clkInhibitePin , 0);
#else
    std::cout << "HC165 enable" << std::endl;
#endif
}

/*!
Записывает данные на выводах регистра в память регистра.
*/
void HC165::loadRegister()
{
    disableClock();
    pulse( registerPins.loadPin );
#if __has_include(<pigpio.h>)
    gpioWrite( registerPins.loadPin , 0);
#endif
    enableClock();
}

/*!
Считывает байт данных из регистра.
\return byte Байт считанных данных
*/
unsigned char HC165::readByte()
{
    unsigned char byte = 0;

    // shiftin
    for(int i = 0; i < 8; i++)
    {
#if __has_include(<pigpio.h>)
        byte |= (gpioRead( registerPins.dataPin ) << (7 - i));

#endif
        pulse( registerPins.clkPin );
    }

    return(byte);
}
