#ifndef PERIPHERALSETTINGS_H
#define PERIPHERALSETTINGS_H

/*!
    \brief Структура для хранения пинов выходного регистра

    Данная структура хранит набор пинов Raspberry Pi для управления выходным регистром 74HC595 в нотации GPIO.
*/
struct HC595Pins{
    const int dataPin = 23;      //595 serial data input
    const int latchClkPin = 25;  //595 latch clock input( STcp )
    const int clkPin = 24;       //595 data clock input( SHcp )
    const int nResetPin = 18;    //595 not reset input( Not MR )
    const int nEnablePin = 16;   //595 not enable input( Not OE )
};

/*!
    \brief Структура для хранения пинов входного регистра

    Данная структура хранит набор пинов Raspberry Pi для управления входным регистром 74HC165 в нотации GPIO.
*/
struct HC165Pins{
    const int dataPin = 4;             //165 serial data output
    const int clkPin = 17;             //165 data clock input
    const int clkInhibitePin = 22;     //165 inhibite clock input
    const int loadPin = 27;            //165 load register input( SH/Not(LD) )
};

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
    //HC595 section
    HC595Pins outputRegisters;
    //HC165 section
    HC165Pins inputRegisters;
    //PWM section
    PWMPins pwm;
    //Encoder section
    // EncoderSettings encoders;
};

#endif // PERIPHERALSETTINGS_H
