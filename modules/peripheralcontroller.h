#ifndef PERIPHERALCONTROLLER_H
#define PERIPHERALCONTROLLER_H

#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <wiringPi.h>

//Protobuf headers
#include "protobuf/control.pb.h"
#include "protobuf/sensors.pb.h"

#include "registers/registercontroller.h"
#include "pwm/pwmcontroller.h"

//HC595 section
#define   DATA_595   23   //595 serial data input
#define   LATCH_CLK_595  25   //595 latch clock input( STcp )
#define   SHIFT_CLK_595 24   //595 data clock input( SHcp )
#define   NOT_RESET_595 18   //595 not reset input( Not MR )
#define   NOT_ENABLE_595 16   //595 not enable input( Not OE )

//HC165 section
#define   DATA_165  4   //165 serial data output
#define   CLK_165  17   //165 data clock input
#define   CLK_INH_165 22   //165 inhibite clock input
#define   LOAD_165 27   //165 load register input( SH/Not(LD) )

//PWM hardware pins
#define PWM_HARD_RIGHT 12 //hardware pwm pin: right wheel motor
#define PWM_HARD_LEFT 13 //hardware pwm pin: left wheel motor

//PWM software pins
#define PWM_SOFT_RIGHT 20 //software pwm pin: right hand motor
#define PWM_SOFT_LEFT 21 //software pwm pin: left hand motor

//Encoder section
#define ENCODER_SECTORS_COUNT 100 // Count sectors on encoders disk
#define MOTOR_FREQ 100 // Motor speed
#define POLLING_FREQ (ENCODER_SECTORS_COUNT*MOTOR_FREQ)*3 // Encoder sampling rate

unsigned char bytes[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

class PeripheralController
{
    RegisterController *registers;
    PWMController *pwm;

    AmurSensors *sensorsPeri;
    AmurControls *controlsPeri;

    int wheelLeftAngle;
    int wheelRightAngle;

    int handLeftInternalAngle;
    int handRightInternalAngle;

    int handLeftOuterAngle;
    int handRightOuterAngle;

    void initPWM();
    void wiringPiInit();

    unsigned char leftOutRegisterToByte();
    unsigned char rightOutRegisterToByte();
public:
    PeripheralController(AmurControls *controls, AmurSensors *sensors);

    void changeWheelsPWM();
    void changeHandsPWM();

    void writeRegisterData();
    void readRegisterData();

    int getWheelLeftAngle() const;
    void setWheelLeftAngle(int value);
    int getWheelRightAngle() const;
    void setWheelRightAngle(int value);

    int getHandLeftInternalAngle() const;
    void setHandLeftInternalAngle(int value);
    int getHandRightInternalAngle() const;
    void setHandRightInternalAngle(int value);

    int getHandLeftOuterAngle() const;
    void setHandLeftOuterAngle(int value);
    int getHandRightOuterAngle() const;
    void setHandRightOuterAngle(int value);
};

#endif // PERIPHERALCONTROLLER_H
