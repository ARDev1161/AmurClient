#ifndef PERIPHERALSETTINGS_H
#define PERIPHERALSETTINGS_H

#include "registers/registerssettings.h"
#include "pwm/pwmsettings.h"

/*!
    \brief Структура для хранения настроек энкодеров

    Данная структура хранит набор настроек для работы с энкодерами.
*/
struct EncoderSettings{
    const int encoderSectorsCount = 100; // Count sectors on encoders disk
    const int maxMotorSpeed = 100;  // Motor speed: rpm
    const int sampleRate = ( encoderSectorsCount * maxMotorSpeed ) * 3; // Encoder sampling rate
};

/*!
    \brief Структура для хранения пинов и настроек оборудования периферии

    Данная структура хранит набор пинов и настроек оборудования периферии.
*/
struct PeripheralSettings{
    //Registers section
    RegisterSettings registers;
    //PWM section
    PWMPins pwm;
    //Encoder section
    // EncoderSettings encoders;
};

#endif // PERIPHERALSETTINGS_H
