#ifndef PERIPHERALCONTROLLER_H
#define PERIPHERALCONTROLLER_H

#include <iostream>
#include <cstdlib>
#include <math.h>

#if __has_include(<pigpio.h>)
    #include <pigpio.h>
#endif

//Timer header
#include "../timer/TimerCallback.h"

//Protobuf headers
#include "../network/protobuf/amur.pb.h"

// Controllers headers
#include "registers/registercontroller.h"
#include "pwm/pwmcontroller.h"

#include "peripheralsettings.h"

/*!
    \brief Класс управления периферией робота

    Данный класс позволяет управлять периферическим оборудование робота.
*/
class PeripheralController: private TimerCallback::Runnable
{
    // Fields

    PeripheralSettings peripheralSettings;

    RegisterController *registers;
    PWMController *pwm;

    TimerCallback peripheralTimer;

    // Buffers
    AMUR::AmurSensors *sensorsPeri;
    AMUR::AmurControls *controlsPeri;

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
    unsigned int prevLeftWheelPWM = 0;
    unsigned int prevRightWheelPWM = 0;

    unsigned int prevLeftHandPWM = 0;
    unsigned int prevRightHandPWM = 0;

    // Functions
    void pigpioInit();
    void initPWM();
    void initRegisters();
    void initTimer();
    void run();

    void checkMotorsTime();

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
public:
    PeripheralController(AMUR::AmurControls *controls, AMUR::AmurSensors *sensors);
    virtual ~PeripheralController();

    void updateData();
};

#endif // PERIPHERALCONTROLLER_H
