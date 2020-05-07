#ifndef SPI_H
#define SPI_H

#include <errno.h>
#include <unistd.h>
#if __has_include(<wiringPiSPI.h>)
    #include <wiringPiSPI.h>
#else
    #include <iostream>
#endif


class SPI
{
    // channel is the wiringPi name for the chip select (or chip enable) pin.
    // Set this to 0 or 1, depending on how it's connected.
    static const int CHANNEL = 1;

public:
    SPI();
    void init();
};

#endif // SPI_H
