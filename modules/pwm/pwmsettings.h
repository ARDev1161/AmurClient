#ifndef PWMSETTINGS_H
#define PWMSETTINGS_H

/*!
    \brief Структура для хранения пинов PWM

    Данная структура хранит набор пинов Raspberry Pi для управления PWM в нотации GPIO.
*/
struct PWMPins{
    const int wheelRightPin = 12; //hardware pwm pin: right wheel motor
    const int wheelLeftPin = 13; //hardware pwm pin: left wheel motor

    const int handRightPin = 20; //software pwm pin: right hand motor
    const int handLeftPin = 21; //software pwm pin: left hand motor
};

#endif // PWMSETTINGS_H
