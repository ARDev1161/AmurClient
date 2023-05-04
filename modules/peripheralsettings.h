#ifndef PERIPHERALSETTINGS_H
#define PERIPHERALSETTINGS_H

#include "registers/registerssettings.h"
#include "pwm/pwmsettings.h"

/*!
    \brief Структура для хранения настроек энкодеров

    Данная структура хранит набор настроек для работы с энкодерами.
*/
struct EncoderSettings{
    const unsigned int encoderSectorsCount = 100; // Count sectors on encoders disk
    const unsigned int maxSpeed = 100;  // Ma speed: rpm
    const unsigned int sampleRate = ( encoderSectorsCount * maxSpeed ) * 3; // Encoder sampling rate
};

/*!
    \brief Структура для хранения настроек энкодеров

    Данная структура хранит набор настроек для работы с моторами.
*/
struct MotorSettings{
    const int maxMotorSpeed = 100;  // Motor speed: rpm
    const int maxCurrent = 100;  // Max current from motor driver, in Ampere.
};


/*!
    \brief Структура для хранения пинов и настроек оборудования периферии

    Данная структура хранит набор пинов и настроек оборудования периферии.
*/
struct PeripheralSettings{
    //Encoder section
    EncoderSettings encoderSettings;
    //Motor section
    MotorSettings motorSettings;
    //Registers section
    RegisterSettings registerSettings;
    //PWM section
    PWMPins pwmSettings;
    //Encoder section
    // EncoderSettings encoders;
};

#endif // PERIPHERALSETTINGS_H
