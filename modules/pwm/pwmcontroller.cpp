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
    #if __has_include(<wiringPi.h>)
        return softPwmCreate(pin, 0, pwmRange);
    #else
        std::cout << "Soft PWM create on - " << pin << std::endl;
        return 0;
    #endif
}

/*!
Изменяет скважность на выводе программного PWM.
\param[in] pin Вывод на котором изменяется скважность программного PWM сигнала
\param[in] dutyCycle Скважность программного PWM сигнала
*/
void PWMController::softPWMChange(int pin, int dutyCycle)
{
    #if __has_include(<wiringPi.h>)
        softPwmWrite(pin, dutyCycle );
    #else
        std::cout << "Soft PWM change on - " << pin << "\t with duty - " << dutyCycle << std::endl;
    #endif
}

/*!
Останавливает программный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором останавливается программный PWM сигнал
*/
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

/*!
Создаёт аппаратный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором создаётся аппаратный PWM сигнал
*/
void PWMController::hardPWMCreate(int pin)
{
    #if __has_include(<wiringPi.h>)
        pinMode(pin, PWM_OUTPUT);
    #else
        std::cout << "Hard PWM create on - " << pin << std::endl;
    #endif
}

/*!
Изменяет скважность на выводе аппаратного PWM.
\param[in] pin Вывод на котором изменяется скважность аппаратного PWM сигнала
\param[in] dutyCycle Скважность аппаратного PWM сигнала
*/
void PWMController::hardPWMChange(int pin, int dutyCycle)
{
    #if __has_include(<wiringPi.h>)
        pwmWrite(pin, dutyCycle);
    #else
        std::cout << "Hard PWM change on - " << pin << "\t to duty - " << dutyCycle << std::endl;
    #endif
}

/*!
Останавливает аппаратный PWM сигнал на выводе Raspberry Pi в нотации GPIO.
\param[in] pin Вывод на котором останавливается аппаратный PWM сигнал
*/
void PWMController::hardPWMStop(int pin)
{
    #if __has_include(<wiringPi.h>)
        pwmWrite(pin, 0);
    #else
        std::cout << "Hard PWM stop on - " << pin << std::endl;
    #endif
}
