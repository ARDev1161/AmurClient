#include "pwmcontroller.h"

/*!
Создаёт экземпляр класса для работы с PWM.
*/
PWMController::PWMController()
{

}

//Software PWM section: time resolution - 100uS

/*!
Создаёт программный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором создаётся программный PWM сигнал
\return Возвращает 0 если при создании PWM сигнала не произошло ошибки
*/
int PWMController::softPWMCreate(int pin)
{
    #if __has_include(<pigpio.h>)
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
int PWMController::softPWMChange(int pin, int dutyCycle)
{
    #if __has_include(<pigpio.h>)
        return gpioPWM(pin, dutyCycle); // Number pin in GPIO notation, 0-31
    #else
        std::cout << "Soft PWM change on - " << pin << "\t with duty - " << dutyCycle << std::endl;
    #endif

    return 0;
}

/*!
Останавливает программный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором останавливается программный PWM сигнал
*/
int PWMController::softPWMStop(int pin)
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
int PWMController::hardPWMCreate(int pin)
{
    #if __has_include(<pigpio.h>)
        return gpioHardwarePWM(pin, freq, 0);
    #else
        std::cout << "Hard PWM create on - " << pin << std::endl;
    #endif

    return 0;
}

/*!
Изменяет скважность на выводе аппаратного PWM.
\param[in] pin Вывод на котором изменяется скважность аппаратного PWM сигнала
\param[in] dutyCycle Скважность аппаратного PWM сигнала
*/
int PWMController::hardPWMChange(int pin, int dutyCycle)
{
    #if __has_include(<pigpio.h>)
        return gpioHardwarePWM(pin, freq, dutyCycle);
    #else
        std::cout << "Hard PWM change on - " << pin << "\t to duty - " << dutyCycle << std::endl;
    #endif

    return 0;
}

/*!
Останавливает аппаратный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором останавливается аппаратный PWM сигнал
*/
int PWMController::hardPWMStop(int pin)
{
    #if __has_include(<pigpio.h>)
        return gpioHardwarePWM(pin, freq, 0);
    #else
        std::cout << "Hard PWM stop on - " << pin << std::endl;
    #endif

    return 0;
}
