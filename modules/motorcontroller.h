#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "encoder.h"
#include "peripheralsettings.h"

class Motor
{
    // Motor & encoder
    MotorSettings *settings;
    Encoder *encoder;
    float current = 0;

public:
    Motor(MotorSettings *motor, EncoderSettings *encoder);
    ~Motor();
    Encoder *getEncoder() const;

    float getCurrent() const;
};

class MotorController
{
    Motor *wheelLeft;
    Motor *wheelRight;

    Motor *handInternalLeft;
    Motor *handInternalRight;
    Motor *handOuterLeft;
    Motor *handOuterRight;
public:
    MotorController(MotorSettings *motor, EncoderSettings *encoder);
    ~MotorController();

    Motor *getWheelLeft() const;
    Motor *getWheelRight() const;
    Motor *getHandInternalLeft() const;
    Motor *getHandInternalRight() const;
    Motor *getHandOuterLeft() const;
    Motor *getHandOuterRight() const;
};

#endif // MOTORCONTROLLER_H
