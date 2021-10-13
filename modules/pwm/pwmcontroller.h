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

    inline unsigned int translateDuty(unsigned int duty, unsigned int gpioRange){
        return ((duty / pwmRange) * (gpioRange / freqHardware)); // 375000000 - for BCM2711. For non BCM2711 use 250M
    }
    inline unsigned int translateDuty(unsigned int duty){
        return (duty / pwmRange); // 375000000 - for BCM2711. For non BCM2711 use 250M
    }
    
public:
    PWMController();

    int hardPWMCreate(unsigned int pin);
    int hardPWMChange(unsigned int pin, unsigned int dutyCycle);
    int hardPWMStop(unsigned int pin);

    int softPWMCreate(unsigned int pin);
    int softPWMChange(unsigned int pin, unsigned int dutyCycle);
    int softPWMStop(unsigned int pin);

    int getPwmRange() const;
    void setPwmRange(unsigned int newPwmRange);

    int getFreqHardware() const;
    void setFreqHardware(unsigned int newFreqHardware);
};

#endif // PWMCONTROLLER_H
