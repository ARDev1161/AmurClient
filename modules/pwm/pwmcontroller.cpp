#include "pwmcontroller.h"

PWMController::PWMController()
{

}

//Software PWM section: time resolution - 100uS
int PWMController::softPWMCreate(int pin)
{
    #if __has_include(<wiringPi.h>)
        return softPwmCreate(pin, 0, pwmRange);
    #else
        std::cout << "Soft PWM create on - " << pin << std::endl;
        return 0;
    #endif
}

void PWMController::softPWMChange(int pin, int dutyCycle)
{
    #if __has_include(<wiringPi.h>)
        softPwmWrite(pin, dutyCycle );
    #else
        std::cout << "Soft PWM change on - " << pin << "\t with duty - " << dutyCycle << std::endl;
    #endif
}

void PWMController::softPWMStop(int pin)
{
    #if __has_include(<wiringPi.h>)
        digitalWrite(notEnable, 1);
        softPwmStop(pin);
    #else
        std::cout << "Soft PWM stop on - " << pin << std::endl;
    #endif
}

//Hardware PWM section
void PWMController::hardPWMCreate(int pin)
{
    #if __has_include(<wiringPi.h>)
        pinMode(pin, PWM_OUTPUT);
    #else
        std::cout << "Hard PWM create on - " << pin << std::endl;
    #endif
}

void PWMController::hardPWMChange(int pin, int dutyCycle)
{
    #if __has_include(<wiringPi.h>)
        pwmWrite(pin, dutyCycle);
    #else
        std::cout << "Hard PWM change on - " << pin << "\t to duty - " << dutyCycle << std::endl;
    #endif
}

void PWMController::hardPWMStop(int pin)
{
    #if __has_include(<wiringPi.h>)
        pwmWrite(pin, 0);
    #else
        std::cout << "Hard PWM stop on - " << pin << std::endl;
    #endif
}
