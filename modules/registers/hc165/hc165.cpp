#include "hc165.h"
 
/*!
Создаёт экземпляр класса для считывания из регистра.
\param[in] pins Структура описывающая пины Raspberry Pi для подключения регистра в нотации GPIO
*/
HC165::HC165(HC165Pins pins):
registerPins(pins)
{
#if __has_include(<pigpio.h>)
    std::cout << "HC165 entity creating..." << std::endl;
    if(gpioSetMode( registerPins.dataPin , PI_INPUT) != 0)
        std::cout << "gpioSetMode HC165 dataPin ERROR!!!" << std::endl;
    if(gpioSetMode( registerPins.loadPin , PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC165 loadPin ERROR!!!" << std::endl;
    if(gpioSetMode( registerPins.clkPin , PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC165 clkPin ERROR!!!" << std::endl;
    if(gpioSetMode( registerPins.clkInhibitePin , PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC165 clkInhibitePin ERROR!!!" << std::endl;

    if(gpioWrite( registerPins.loadPin , 0) != 0)
        std::cout << "gpioWrite HC165 loadPin ERROR!!!" << std::endl;
    if(gpioWrite( registerPins.clkPin , 0) != 0)
        std::cout << "gpioWrite HC165 clkPin ERROR!!!" << std::endl;
    if(gpioWrite( registerPins.clkInhibitePin , 0) != 0)
        std::cout << "gpioWrite HC165 clkInhibitePin ERROR!!!" << std::endl;
#endif
    std::cout << "Created HC165 entity" << std::endl;
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
#endif
}

/*!
Выключает регистр.
*/
void HC165::disableClock()
{
#if __has_include(<pigpio.h>)

#endif
}

/*!
Включает регистр.
*/
void HC165::enableClock()
{
#if __has_include(<pigpio.h>)
    gpioWrite( registerPins.clkInhibitePin , 0);
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
