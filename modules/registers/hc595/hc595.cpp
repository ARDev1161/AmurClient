#include "hc595.h"

/*!
Создаёт экземпляр класса для записи в регистр.
\param[in] pins Структура описывающая пины Raspberry Pi для подключения регистра в нотации GPIO
*/
HC595::HC595(RegisterSettings *settings):
settings(settings)
{
    gpioInit();
}

HC595::HC595()
{
    settings = new RegisterSettings();
    gpioInit();
}

void HC595::gpioInit()
{
#if __has_include(<pigpio.h>)
    std::cout << "HC595 entity creating..." << std::endl;
        
    if(gpioSetMode( settings->hc595Pins.dataPin, PI_OUTPUT) != 0)
        std::cerr << "gpioSetMode HC595 dataPin ERROR!!!" << std::endl;
    if(gpioSetMode( settings->hc595Pins.latchClkPin, PI_OUTPUT) != 0)
        std::cerr << "gpioSetMode HC595 latchClkPin ERROR!!!" << std::endl;
    if(gpioSetMode( settings->hc595Pins.clkPin, PI_OUTPUT) != 0)
        std::cerr << "gpioSetMode HC595 clkPin ERROR!!!" << std::endl;
    if(gpioSetMode( settings->hc595Pins.nResetPin, PI_OUTPUT) != 0)
        std::cerr << "gpioSetMode HC595 nResetPin ERROR!!!" << std::endl;
    if(gpioSetMode( settings->hc595Pins.nEnablePin, PI_OUTPUT) != 0)
        std::cerr << "gpioSetMode HC595 nEnablePin ERROR!!!" << std::endl;

    if(gpioSetPullUpDown( settings->hc595Pins.dataPin, PI_PUD_DOWN) != 0)
        std::cerr << "gpioSetPullUpDown HC595 dataPin ERROR!!!" << std::endl;
    if(gpioSetPullUpDown( settings->hc595Pins.latchClkPin, PI_PUD_DOWN) != 0)
        std::cerr << "gpioSetPullUpDown HC595 latchClkPin ERROR!!!" << std::endl;
    if(gpioSetPullUpDown( settings->hc595Pins.clkPin, PI_PUD_DOWN) != 0)
        std::cerr << "gpioSetPullUpDown HC595 clkPin ERROR!!!" << std::endl;
    if(gpioSetPullUpDown( settings->hc595Pins.nResetPin, PI_PUD_DOWN) != 0)
        std::cerr << "gpioSetPullUpDown HC595 nResetPin ERROR!!!" << std::endl;
    if(gpioSetPullUpDown( settings->hc595Pins.nEnablePin, PI_PUD_DOWN) != 0)
        std::cerr << "gpioSetPullUpDown HC595 nEnablePin ERROR!!!" << std::endl;

    if(gpioWrite( settings->hc595Pins.dataPin, 0) != 0)
        std::cerr << "gpioWrite HC595 dataPin ERROR!!!" << std::endl;
    if(gpioWrite( settings->hc595Pins.latchClkPin, 0) != 0)
        std::cerr << "gpioWrite HC595 latchClkPin ERROR!!!" << std::endl;
    if(gpioWrite( settings->hc595Pins.clkPin, 0) != 0)
        std::cerr << "gpioWrite HC595 clkPin ERROR!!!" << std::endl;
    if(gpioWrite( settings->hc595Pins.nResetPin, 1) != 0)
        std::cerr << "gpioWrite HC595 nResetPin ERROR!!!" << std::endl;
    if(gpioWrite( settings->hc595Pins.nEnablePin, 0) != 0)
        std::cerr << "gpioWrite HC595 nEnablePin ERROR!!!" << std::endl;
#endif
    std::cout << "Created HC595 entity" << std::endl;
}

/*!
Подаёт импульс на указанный пин управления регистра.
\param[in] pin Пин GPIO для управления регистром
*/
inline void HC595::pulse(int pin)
{
#if __has_include(<pigpio.h>)
    gpioWrite(pin, 1);
    usleep(settings->general.usPulseDelay);
    gpioWrite(pin, 0);
    usleep(settings->general.usPulseDelay);
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
        gpioWrite( settings->hc595Pins.dataPin, ( (byte & (0x80 >> i)) > 0 ) );
        pulse( settings->hc595Pins.clkPin );
    #endif
    }
}

/*!
Выводит записанные данные на выводы регистра.
*/
void HC595::latchSignal()
{
    pulse( settings->hc595Pins.latchClkPin );
}

/*!
Сбрасывает данные внутри регистра.
*/
void HC595::reset()
{
    pulse( settings->hc595Pins.nResetPin );
#if __has_include(<pigpio.h>)
    gpioWrite( settings->hc595Pins.nResetPin, 1);
#endif
}

/*!
Включает регистр.
*/
void HC595::enable()
{
#if __has_include(<pigpio.h>)
    gpioWrite( settings->hc595Pins.nEnablePin , 0);
#endif
}

/*!
Выключает регистр.
*/
void HC595::disable()
{
#if __has_include(<pigpio.h>)
    gpioWrite(  settings->hc595Pins.nEnablePin , 1);
#endif
}
