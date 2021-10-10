#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include "pwmsettings.h"

#include <iostream>

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#endif


/*!
    \brief Класс управления PWM сигналами

    Данный класс позволяет управлять PWM сигналами робота.
*/
class PWMController
{
    int pwmRange = 255; //Max input value, min value is 0
    int freqHardware = 20000; // PWM frequency in hertz

    inline int translateDuty(int duty, int newMax){
        return ((duty * newMax) / pwmRange);
    }
public:
    PWMController();

    int hardPWMCreate(int pin);
    int hardPWMChange(int pin, int dutyCycle);
    int hardPWMStop(int pin);

    int softPWMCreate(int pin);
    int softPWMChange(int pin, int dutyCycle);
    int softPWMStop(int pin);

    int getPwmRange() const;
    void setPwmRange(int newPwmRange);

    int getFreqHardware() const;
    void setFreqHardware(int newFreqHardware);
};

#endif // PWMCONTROLLER_H
