#include "pwmcontroller.h"

/*!
Создаёт экземпляр класса для работы с PWM.
*/
PWMController::PWMController()
{
    std::cout << "Created PWMController entity" << std::endl;
}

//Software PWM section: time resolution - 100uS

/*!
Создаёт программный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором создаётся программный PWM сигнал
\return Возвращает 0 если при создании PWM сигнала не произошло ошибки
*/
int PWMController::softPWMCreate(unsigned int pin)
{
    #if __has_include(<pigpio.h>)
        gpioSetMode(pin, PI_OUTPUT);
        return gpioPWM(pin, 0); // Number pin in GPIO notation, 0-31
    #else
        std::cout << "Soft PWM create on - " << pin << std::endl;
    #endif
    return 0;
}

/*!
Изменяет скважность на выводе программного PWM.
\param[in] pin Вывод на котором изменяется скважность программного PWM сигнала
\param[in] dutyCycle Скважность программного PWM сигнала
*/
int PWMController::softPWMChange(unsigned int pin, unsigned int dutyCycle)
{
    #if __has_include(<pigpio.h>)
        return gpioPWM(pin, translateDuty(dutyCycle, 255) ); // Number pin in GPIO notation, 0-31
    #else
        std::cout << "Soft PWM change on - " << pin << "\t with duty - " << dutyCycle << std::endl;
    #endif
    return 0;
}

/*!
Останавливает программный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором останавливается программный PWM сигнал
*/
int PWMController::softPWMStop(unsigned int pin)
{
    #if __has_include(<pigpio.h>)
        return gpioPWM(pin, 0); // Number pin in GPIO notation, 0-31
    #else
        std::cout << "Soft PWM stop on - " << pin << std::endl;
    #endif
    return 0;
}

//Hardware PWM section

/*!
Создаёт аппаратный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором создаётся аппаратный PWM сигнал
*/
int PWMController::hardPWMCreate(unsigned int pin)
{
    #if __has_include(<pigpio.h>)
        gpioSetMode(pin, PI_OUTPUT);
        return gpioHardwarePWM(pin, freqHardware, 0);
    #endif
    return 0;
}

/*!
Изменяет скважность на выводе аппаратного PWM.
\param[in] pin Вывод на котором изменяется скважность аппаратного PWM сигнала
\param[in] dutyCycle Скважность аппаратного PWM сигнала
*/
int PWMController::hardPWMChange(unsigned int pin, unsigned int dutyCycle)
{
    #if __has_include(<pigpio.h>)
        return gpioHardwarePWM(pin, freqHardware, translateDuty(dutyCycle, 375000000) );
    #else
        std::cout << "Hard PWM change on - " << pin << "\t to duty - " << dutyCycle << std::endl;
    #endif
    return 0;
}

/*!
Останавливает аппаратный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором останавливается аппаратный PWM сигнал
*/
int PWMController::hardPWMStop(unsigned int pin)
{
    #if __has_include(<pigpio.h>)
        return gpioHardwarePWM(pin, freqHardware, 0);
    #endif
    return 0;
}

int PWMController::getPwmRange() const
{
    return pwmRange;
}
void PWMController::setPwmRange(unsigned int newPwmRange)
{
    pwmRange = newPwmRange;
}

int PWMController::getFreqHardware() const
{
    return freqHardware;
}

void PWMController::setFreqHardware(unsigned int newFreqHardware)
{
    freqHardware = newFreqHardware;
}
