#ifndef SPI_H
#define SPI_H

#include <errno.h>
#include <unistd.h>
#if __has_include(<wiringPiSPI.h>)
    #include <wiringPiSPI.h>
#else
    #include <iostream>
#endif


/*!
    \brief Класс работы с интерфейсом SPI

    Данный класс инкапсулирует взаимодействие с интерфейсом SPI.
*/
class SPI
{
    // channel is the wiringPi name for the chip select (or chip enable) pin.
    // Set this to 0 or 1, depending on how it's connected.
    static const int CHANNEL = 1;

public:
    SPI();
    int init();
};

#endif // SPI_H
