#ifndef I2C_H
#define I2C_H

#include <errno.h>
#include <unistd.h>

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#else
    #include <iostream>
#endif

#define RS (sizeof(gpioReport_t))

#define SCL_FALLING 0
#define SCL_RISING  1
#define SCL_STEADY  2

#define SDA_FALLING 0
#define SDA_RISING  4
#define SDA_STEADY  8

/*!
    \brief Класс работы с интерфейсом I2C

    Данный класс инкапсулирует взаимодействие с интерфейсом I2C.
*/
class I2C
{
    int SCL, SDA, xSCL;
    int r;

    // channel is the wiringPi name for the chip select (or chip enable) pin.
    // Set this to 0 or 1, depending on how it's connected.
    static const int CHANNEL = 1;

    int fd, result;
    unsigned char buffer[100];

    void parse_I2C(int SCL, int SDA);
public:
    I2C();
    void init();
    int scanBus(int gSCL, int gSDA);
};

#endif // I2C_H
