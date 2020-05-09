#ifndef PERIPHERALSETTINGS_H
#define PERIPHERALSETTINGS_H

struct HC595Pins{
    int outputDataPin = 23;      //595 serial data input
    int outputLatchClkPin = 25;  //595 latch clock input( STcp )
    int outputClkPin = 24;       //595 data clock input( SHcp )
    int outputNResetPin = 18;    //595 not reset input( Not MR )
    int outputNEnablePin = 16;   //595 not enable input( Not OE )
};

struct HC165Pins{
    int dataPin = 4;             //165 serial data output
    int clkPin = 17;             //165 data clock input
    int clkInhibitePin = 22;     //165 inhibite clock input
    int loadPin = 27;            //165 load register input( SH/Not(LD) )
};

struct PWMPins{
    int wheelRightPin = 12; //hardware pwm pin: right wheel motor
    int wheelLeftPin = 13; //hardware pwm pin: left wheel motor

    int handRightPin = 20; //software pwm pin: right hand motor
    int handLeftPin = 21; //software pwm pin: left hand motor
};

#define ENCODER_SECTORS_COUNT 100 // Count sectors on encoders disk
#define MOTOR_FREQ 100 // Motor speed: rpm
#define POLLING_FREQ (ENCODER_SECTORS_COUNT*MOTOR_FREQ)*3 // Encoder sampling rate

struct EncoderSettings{
    int sampleRate = POLLING_FREQ;
};

struct PeripheralSettings{
    //HC595 section
    HC595Pins outputRegisters;
    //HC165 section
    HC165Pins inputRegisters;
    //PWM section
    PWMPins pwm;
    //Encoder section
    EncoderSettings encoders;
};

#endif // PERIPHERALSETTINGS_H
