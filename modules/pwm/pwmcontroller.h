#ifndef PWMCONTROLLER_H
#define PWMCONTROLLER_H

#include <wiringPi.h>
#include <softPwm.h>


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
