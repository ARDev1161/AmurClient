#ifndef UART_H
#define UART_H

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <chrono>
#include <thread>

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#else
    #include <iostream>
#endif


/*!
    \brief Класс работы с интерфейсом UART

    Данный класс инкапсулирует взаимодействие с интерфейсом UART.
*/
class UART
{
public:
    UART();
    int init();
};

#endif // UART_H
