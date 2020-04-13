#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include <wiringPi.h>
#include <softPwm.h>

#include "dma/dmapwm.h"

class PWMController
{
    int pwmRange = 255;

public:
    PWMController();

    void hardPWMCreate(int pin);
    int softPWMCreate(int pin);
    void dmaPWMCreate(int pin);

    void hardPWMChange(int pin, int dutyCycle);
    void softPWMChange(int pin, int dutyCycle);
    void dmaPWMChange(int pin, int dutyCycle);

    void hardPWMStop(int pin);
    void softPWMStop(int pin);
    void dmaPWMStop(int pin);


};

#endif // PWMCONTROLLER_H
