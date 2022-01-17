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
    typedef unsigned char byte_t;

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

    int open(); // returns a handle for the device at the address on the I2C bus.
    int close(unsigned handle);
    int scanBus(int gSCL, int gSDA);

    int read(byte_t handle, byte_t value);
    int write(byte_t handle, byte_t value);
    int writeBit(byte_t handle, bool value);

    int readRegByte(byte_t handle, byte_t value); // Read 8 bits from device register
    int writeRegByte(byte_t handle, byte_t value); // Write 8 bits to device register

    int readRegWord(byte_t handle, int value); // Read 16 bits from device register
    int writeRegWord(byte_t handle, int value); // Write 16 bits to device register
    int exchangeRegWord(byte_t handle, int value); // Write 16 bits to device register & get 16 bit as answer

    int readRegBlock(unsigned handle, unsigned i2cReg, char *buf); // Read block of data up to 32 bytes from device register
    int writeRegBlock(unsigned handle, unsigned i2cReg, char *buf, unsigned count); // Write block of data up to 32 bytes to device register
    int exchangeRegBlock(unsigned handle, unsigned i2cReg, char *buf, unsigned count); // Write block of data up to 32 bytes to device register & write answer to *buf

    int readRegI2CBlock(unsigned handle, unsigned i2cReg, char *buf, unsigned count); // Read I2C block of data up to 32 bytes from device register
    int writeRegI2CBlock(unsigned handle, unsigned i2cReg, char *buf, unsigned count); // Write I2C block of data up to 32 bytes to device register
};

#endif // I2C_H
