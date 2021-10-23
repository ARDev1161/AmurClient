#include "motorcontroller.h"

MotorController::MotorController(MotorSettings *motor, EncoderSettings *encoder)
{
    wheelLeft = new Motor(motor, encoder);
    wheelRight = new Motor(motor, encoder);

    handInternalLeft = new Motor(motor, encoder);
    handInternalRight = new Motor(motor, encoder);
    handOuterLeft = new Motor(motor, encoder);
    handOuterRight = new Motor(motor, encoder);
}

MotorController::~MotorController()
{
    delete wheelLeft;
    delete wheelRight;

    delete handInternalLeft;
    delete handInternalRight;
    delete handOuterLeft;
    delete handOuterRight;
}

Motor *MotorController::getWheelLeft() const
{
    return wheelLeft;
}

Motor *MotorController::getWheelRight() const
{
    return wheelRight;
}

Motor *MotorController::getHandInternalLeft() const
{
    return handInternalLeft;
}

Motor *MotorController::getHandInternalRight() const
{
    return handInternalRight;
}

Motor *MotorController::getHandOuterLeft() const
{
    return handOuterLeft;
}

Motor *MotorController::getHandOuterRight() const
{
    return handOuterRight;
}

// Motor class

float Motor::getCurrent() const
{
    return current;
}

Encoder *Motor::getEncoder() const
{
    return encoder;
}

Motor::Motor(MotorSettings *motor, EncoderSettings *encoderSettings):
    settings(motor)
{
    encoder = new Encoder(encoderSettings);
}

Motor::~Motor()
{
    delete encoder;
}
