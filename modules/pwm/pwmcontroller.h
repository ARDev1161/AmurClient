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
    unsigned int pwmRange = 255; //Max input value, min value is 0
    unsigned int freqHardware = 200; // PWM frequency in hertz

    inline unsigned int translateDuty(unsigned int duty, unsigned int newMax){
        return ((duty / pwmRange) * (375000000 / freqHardware)); // For non BCM2711 use 250M
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
