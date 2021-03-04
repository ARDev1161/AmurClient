#include "hc595.h"

/*!
Создаёт экземпляр класса для записи в регистр.
\param[in] pins Структура описывающая пины Raspberry Pi для подключения регистра в нотации GPIO
*/
HC595::HC595(HC595Pins pins):
registerPins(pins)
{
#if __has_include(<pigpio.h>)
    std::cout << "HC595 entity creating..." << std::endl;
    if(gpioSetMode( registerPins.dataPin, PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC595 dataPin ERROR!!!" << std::endl;
    if(gpioSetMode( registerPins.latchClkPin, PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC595 latchClkPin ERROR!!!" << std::endl;
    if(gpioSetMode( registerPins.clkPin, PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC595 clkPin ERROR!!!" << std::endl;
    if(gpioSetMode( registerPins.nResetPin, PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC595 nResetPin ERROR!!!" << std::endl;
    if(gpioSetMode( registerPins.nEnablePin, PI_OUTPUT) != 0)
        std::cout << "gpioSetMode HC595 nEnablePin ERROR!!!" << std::endl;

    if(gpioWrite( registerPins.dataPin, 0) != 0)
        std::cout << "gpioWrite HC595 dataPin ERROR!!!" << std::endl;
    if(gpioWrite( registerPins.latchClkPin, 0) != 0)
        std::cout << "gpioWrite HC595 latchClkPin ERROR!!!" << std::endl;
    if(gpioWrite( registerPins.clkPin, 0) != 0)
        std::cout << "gpioWrite HC595 clkPin ERROR!!!" << std::endl;
    if(gpioWrite( registerPins.nResetPin, 1) != 0)
        std::cout << "gpioWrite HC595 nResetPin ERROR!!!" << std::endl;
    if(gpioWrite( registerPins.nEnablePin, 0) != 0)
        std::cout << "gpioWrite HC595 nEnablePin ERROR!!!" << std::endl;
#endif

    this->reset();
    std::cout << "Created HC595 entity" << std::endl;
}

/*!
Подаёт импульс на указанный пин управления регистра.
\param[in] pin Пин GPIO для управления регистром
*/
inline void HC595::pulse(int pin)
{
#if __has_include(<pigpio.h>)
    gpioWrite(pin, 0);
    gpioWrite(pin, 1);
    gpioWrite(pin, 0);
#endif
}

/*!
Записывает байт данных в регистр.
\param[in] byte Байт записываемых данных
*/
void HC595::writeByte(unsigned char byte)
{
    int i; 
    for(i=0;i<8;i++){
    #if __has_include(<pigpio.h>)
        gpioWrite( registerPins.dataPin, (byte & (0x80 >> i)) );
        pulse( registerPins.clkPin );
    #endif
    }
} 

/*!
Выводит записанные данные на выводы регистра.
*/
void HC595::latchSignal()
{
    pulse( registerPins.latchClkPin );
}

/*!
Сбрасывает данные внутри регистра.
*/
void HC595::reset()
{
    pulse( registerPins.nResetPin );
}

/*!
Включает регистр.
*/
void HC595::enable()
{
#if __has_include(<pigpio.h>)
    gpioWrite( registerPins.nEnablePin , 0);
#endif
}

/*!
Выключает регистр.
*/
void HC595::disable()
{
#if __has_include(<pigpio.h>)
    gpioWrite(  registerPins.nEnablePin , 1);
#endif
}
