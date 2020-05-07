#ifndef PERIPHERALCONTROLLER_H
#define PERIPHERALCONTROLLER_H

#include <iostream>
#include <cstdlib>
#include <math.h>

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
#endif

#include "timer/cppTimer/CppTimerCallback.h"

//Protobuf headers
#include "protobuf/controls.pb.h"
#include "protobuf/sensors.pb.h"

// Controllers headers
#include "registers/registercontroller.h"
#include "pwm/pwmcontroller.h"


//HC595 section
#define   DATA_595   23   //595 serial data input
#define   LATCH_CLK_595  25   //595 latch clock input( STcp )
#define   SHIFT_CLK_595 24   //595 data clock input( SHcp )
#define   NOT_RESET_595 18   //595 not reset input( Not MR )
#define   NOT_ENABLE_595 16   //595 not enable input( Not OE )

//HC165 sectionunsigned long now
#define   DATA_165  4   //165 serial data output
#define   CLK_165  17   //165 data clock input
#define   CLK_INH_165 22   //165 inhibite clock input
#define   LOAD_165 27   //165 load register input( SH/Not(LD) )

//PWM hardware pins
#define PWM_WHEEL_RIGHT 12 //hardware pwm pin: right wheel motor
#define PWM_WHEEL_LEFT 13 //hardware pwm pin: left wheel motor

//PWM software pins
#define PWM_HAND_RIGHT 20 //software pwm pin: right hand motor
#define PWM_HAND_LEFT 21 //software pwm pin: left hand motor

//Encoder section
#define ENCODER_SECTORS_COUNT 100 // Count sectors on encoders disk
#define MOTOR_FREQ 100 // Motor speed: rpm
#define POLLING_FREQ (ENCODER_SECTORS_COUNT*MOTOR_FREQ)*3 // Encoder sampling rate

class PeripheralController: public CppTimerCallback::Runnable
{
    // Fields

    RegisterController *registers;
    PWMController *pwm;

    CppTimerCallback peripheralTimer;

    // Buffers
    AmurSensors *sensorsPeri;
    AmurControls *controlsPeri;

    // Motor angles
    int wheelLeftAngle;
    int wheelRightAngle;

    int handLeftInternalAngle;
    int handRightInternalAngle;
    int handLeftOuterAngle;
    int handRightOuterAngle;

    // Previous state of registers
    unsigned char prevLeftHC165 = 0x00;
    unsigned char prevRightHC165 = 0x00;

    unsigned char prevLeftHC595 = 0x00;
    unsigned char prevRightHC595 = 0x00;

    // Functions
    void initPWM();
    void wiringPiInit();

    void changeWheelsPWM();
    void changeHandsPWM();

    void writeRegisterData();
    void readRegisterData();

    unsigned char leftOutRegisterToByte(); // Generate output byte from protobuf
    unsigned char rightOutRegisterToByte(); // Generate output byte from protobuf

    void parseBytesHC165(unsigned char right, unsigned char left); // Parsing input bytes to encoders angles

    void writeEncodersAngles(); // Write encoders angles to protobuf
    inline void getChangeEncoderAngle(unsigned char addrA,
                                      unsigned char addrB,
                                      unsigned char const byte,
                                      unsigned char const previousByte,
                                      int *const angle);
    // Peripheral timer methods
    void initTimer();
    void run();

    void checkMotorsTime();
public:
    PeripheralController(AmurControls *controls, AmurSensors *sensors);
    virtual ~PeripheralController();

    void updateData();

};

#endif // PERIPHERALCONTROLLER_H
