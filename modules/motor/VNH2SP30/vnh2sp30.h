#ifndef VNH2SP30_H
#define VNH2SP30_H

#include "wiringPi.h"

class VNH2SP30
{
    int motorSpeed = 0;

    int inputA = 0;
    int inputB = 0;
    int enable = 0;
    int pwm = 0;

public:
    VNH2SP30(int inputAPin, int inputBPin, int enablePin, int pwmPin);

    void enableMotor();
    void disableMotor();
    void setPWM(int dutyCycle);

    void forward();
    void backward();

};

#endif // VNH2SP30_H
