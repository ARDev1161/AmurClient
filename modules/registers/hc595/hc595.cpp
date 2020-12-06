#include "hc595.h"

/*!
Создаёт экземпляр класса для записи в регистр.
\param[in] pins Структура описывающая пины Raspberry Pi для подключения регистра в нотации GPIO
*/
HC595::HC595(HC595Pins pins):
registerPins(pins)
{
#if __has_include(<pigpio.h>)
    gpioSetMode( registerPins.dataPin, PI_OUTPUT);
    gpioSetMode( registerPins.latchClkPin, PI_OUTPUT);
    gpioSetMode( registerPins.clkPin, PI_OUTPUT);
    gpioSetMode( registerPins.nResetPin, PI_OUTPUT);
    gpioSetMode( registerPins.nEnablePin, PI_OUTPUT);

    gpioWrite( registerPins.dataPin, 0);
    gpioWrite( registerPins.latchClkPin, 0);
    gpioWrite( registerPins.clkPin, 0);
    gpioWrite( registerPins.nResetPin, 1);
    gpioWrite( registerPins.nEnablePin, 0);

#elif __has_include(<wiringPi.h>)
    pinMode( registerPins.dataPin, OUTPUT);
    pinMode( registerPins.latchClkPin, OUTPUT);
    pinMode( registerPins.clkPin, OUTPUT);
    pinMode( registerPins.nResetPin, OUTPUT);
    pinMode( registerPins.nEnablePin, OUTPUT);

    digitalWrite( registerPins.dataPin, 0);
    digitalWrite( registerPins.latchClkPin, 0);
    digitalWrite( registerPins.clkPin, 0);
    digitalWrite( registerPins.nResetPin, 1);
    digitalWrite( registerPins.nEnablePin, 0);
#endif
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

#elif __has_include(<wiringPi.h>)
    digitalWrite(pin, 0);
    digitalWrite(pin, 1);

#else
    std::cout << "HC595 Pulse on " << pin << std::endl;
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
        gpioWrite( registerPins.dataPin, ((byte & (0x80 >> i)) > 0));
        pulse( registerPins.clkPin );

    #elif __has_include(<wiringPi.h>)
        digitalWrite( registerPins.dataPin, ((byte & (0x80 >> i)) > 0));
        pulse( registerPins.clkPin );

    #else
        std::cout << "HC595 Write bit -  " << i << " from " << byte << std::endl;
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

#elif __has_include(<wiringPi.h>)
    digitalWrite( registerPins.nEnablePin , 0);

#else
    std::cout << "HC595 enable" << std::endl;
#endif
}

/*!
Выключает регистр.
*/
void HC595::disable()
{
#if __has_include(<pigpio.h>)
    gpioWrite(  registerPins.nEnablePin , 1);

#elif __has_include(<wiringPi.h>)
    digitalWrite(  registerPins.nEnablePin , 1);
#else
    std::cout << "HC595 disable" << std::endl;
#endif
}
