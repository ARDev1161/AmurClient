#ifndef I2C_H
#define I2C_H

#include <errno.h>
#include <unistd.h>

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#else
    #include <iostream>
#endif

/*!
    \brief Класс работы с интерфейсом I2C

    Данный класс инкапсулирует взаимодействие с интерфейсом I2C.
*/
class I2C
{
    // channel is the wiringPi name for the chip select (or chip enable) pin.
    // Set this to 0 or 1, depending on how it's connected.
    static const int CHANNEL = 1;

    int fd, result;
    unsigned char buffer[100];

public:
    I2C();
    void init();
};

#endif // I2C_H
