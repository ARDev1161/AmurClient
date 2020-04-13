#include "vnh2sp30.h"

VNH2SP30::VNH2SP30(int inputAPin, int inputBPin, int enablePin, int pwmPin):
inputA(inputAPin), inputB(inputBPin), enable(enablePin), pwm(pwmPin)
{
    pinMode(inputA, OUTPUT);
    pinMode(inputB, OUTPUT);
    pinMode(enable, OUTPUT);
}

void VNH2SP30::enableMotor()
{
    digitalWrite(enable, 1);
}

void VNH2SP30::disableMotor()
{
    digitalWrite(enable, 0);
}

void VNH2SP30::setPWM(int dutyCycle)
{
    motorSpeed = dutyCycle;
}

void VNH2SP30::forward()
{
    digitalWrite(inputA, 1);
    digitalWrite(inputB, 0);
}

void VNH2SP30::backward()
{
    digitalWrite(inputA, 0);
    digitalWrite(inputB, 1);
}
