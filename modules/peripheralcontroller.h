#ifndef PERIPHERALCONTROLLER_H
#define PERIPHERALCONTROLLER_H

#include <iostream>
#include <cstdlib>
#include <math.h>

#if __has_include(<wiringPi.h>)
    #include <wiringPi.h>
#endif

#include "timer/TimerCallback.h"

//Protobuf headers
#include "protobuf/controls.pb.h"
#include "protobuf/sensors.pb.h"

// Controllers headers
#include "registers/registercontroller.h"
#include "pwm/pwmcontroller.h"

#include "peripheralsettings.h"

/*!
    \brief Класс управления периферией робота

    Данный класс позволяет управлять периферическим оборудование робота.
*/
class PeripheralController: public TimerCallback::Runnable
{
    // Fields

    PeripheralSettings settings;

    RegisterController *registers;
    PWMController *pwm;

    TimerCallback peripheralTimer;

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

    // Previous state of PWM
    int prevLeftWheelPWM = 0;
    int prevRightWheelPWM = 0;

    int prevLeftHandPWM = 0;
    int prevRightHandPWM = 0;

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
