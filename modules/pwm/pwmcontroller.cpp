#include "pwmcontroller.h"

PWMController::PWMController()
{

}

//Software PWM section: time resolution - 100uS
int PWMController::softPWMCreate(int pin)
{
    return softPwmCreate(pin, 0, pwmRange);
}
void PWMController::softPWMChange(int pin, int dutyCycle)
{
    softPwmWrite(pin, dutyCycle );
}
void PWMController::softPWMStop(int pin)
{
    softPwmStop(pin);
}

//Hardware PWM section
void PWMController::hardPWMCreate(int pin)
{
    pinMode(pin, PWM_OUTPUT);
}
void PWMController::hardPWMChange(int pin, int dutyCycle)
{
    pwmWrite(pin, dutyCycle);
}
void PWMController::hardPWMStop(int pin)
{
    pwmWrite(pin, 0);
}
