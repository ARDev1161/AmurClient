#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include "pwmsettings.h"

#if __has_include(<wiringPi.h>)
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

public:
    PWMController();

    void hardPWMCreate(int pin);
    int softPWMCreate(int pin);

    void hardPWMChange(int pin, int dutyCycle);
    void softPWMChange(int pin, int dutyCycle);

    void hardPWMStop(int pin);
    void softPWMStop(int pin);

};

#endif // PWMCONTROLLER_H
