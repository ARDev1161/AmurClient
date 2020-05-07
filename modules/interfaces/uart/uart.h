#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <chrono>
#include <thread>

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
    #include <wiringSerial.h>
#else
    #include <iostream>
#endif


class UART
{
public:
    UART();
    int init();
};

#endif // UART_H
