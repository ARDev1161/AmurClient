#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include "pwmsettings.h"

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#elif __has_include(<wiringPi.h>)
    #include <wiringPi.h>
    #include <softPwm.h>
#else
    #include <iostream>
#endif


/*!
    \brief Класс управления PWM сигналами

    Данный класс позволяет управлять PWM сигналами робота.
*/
class PWMController
{
    int pwmRange = 255;
    int freq = 20; // PWM frequency in kilohertz

public:
    PWMController();

    int hardPWMCreate(int pin);
    int hardPWMChange(int pin, int dutyCycle);
    int hardPWMStop(int pin);

    int softPWMCreate(int pin);
    int softPWMChange(int pin, int dutyCycle);
    int softPWMStop(int pin);

};

#endif // PWMCONTROLLER_H
