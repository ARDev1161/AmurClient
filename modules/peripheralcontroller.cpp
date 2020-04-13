#include "peripheralcontroller.h"

PeripheralController::PeripheralController(AmurControls *controls, AmurSensors *sensors):
     sensorsPeri(sensors), controlsPeri(controls)
{
    wiringPiInit();
    registers = new RegisterController(DATA_595, SHIFT_CLK_595, LATCH_CLK_595, NOT_RESET_595, NOT_ENABLE_595,
                                       DATA_165, LOAD_165, CLK_165, CLK_INH_165);
    pwm = new PWMController();
    initPWM();
}

void PeripheralController::wiringPiInit()
{
    if(wiringPiSetupGpio() != 0) //setup GPIO, this uses actual BCM pin numbers
    {
        printf("setup wiringPi failed !");
        abort();
    }
}

void PeripheralController::initPWM()
{
    pwm->hardPWMCreate(PWM_HARD_RIGHT);
    pwm->hardPWMCreate(PWM_HARD_LEFT);

    pwm->softPWMCreate(PWM_SOFT_RIGHT);
    pwm->softPWMCreate(PWM_SOFT_LEFT);
}

unsigned char PeripheralController::leftOutRegisterToByte()
{
    unsigned char byte = 0x00; //((byte & (0x80 >> i)) > 0)

    // first bit is empty - pin is free(freeOutPinL)

    // enable wheel left motor
    byte |= ( abs(controlsPeri->mutable_wheelmotors()->leftpower()) > 0);
    byte <<=1;

    // enable hand left motor
    byte |= ( abs(controlsPeri->mutable_handmotors()->leftpower()) > 0);
    byte <<=1;

    // B2 input: wheel left motor
    byte |= ( controlsPeri->mutable_wheelmotors()->leftpower() < 0);
    byte <<=1;

    // B1 input: hand left motor
    byte |= ( controlsPeri->mutable_handmotors()->leftpower() < 0);
    byte <<=1;

    // A1 input: hand left motor
    byte |= ( controlsPeri->mutable_handmotors()->leftpower() > 0);
    byte <<=1;

    // A2 input: wheel left motor
    byte |= ( controlsPeri->mutable_wheelmotors()->leftpower() > 0);
    byte <<=1;

    // left relay bit
    byte |= controlsPeri->mutable_handmotors()->leftrelay();
    byte <<=1;

    return byte;
}
unsigned char PeripheralController::rightOutRegisterToByte()
{
    unsigned char byte = 0x00;

    // first bit is empty - pin is free(freeOutPinR)

    // enable hand right motor
    byte |= ( abs(controlsPeri->mutable_handmotors()->rightpower()) > 0);
    byte <<=1;

    // enable wheel right motor
    byte |= ( abs(controlsPeri->mutable_wheelmotors()->rightpower()) > 0);
    byte <<=1;

    // B2 input: hand right motor
    byte |= ( controlsPeri->mutable_handmotors()->rightpower() < 0);
    byte <<=1;

    // B1 input: wheel right motor
    byte |= ( controlsPeri->mutable_wheelmotors()->rightpower() < 0);
    byte <<=1;

    // A1 input: wheel right motor
    byte |= ( controlsPeri->mutable_wheelmotors()->rightpower() > 0);
    byte <<=1;

    // A2 input: hand right motor
    byte |= ( controlsPeri->mutable_handmotors()->rightpower() > 0);
    byte <<=1;

    // right relay bit
    byte |= controlsPeri->mutable_handmotors()->rightrelay();
    byte <<=1;

    return byte;
}

void PeripheralController::changeWheelsPWM()
{
    pwm->hardPWMChange(PWM_HARD_RIGHT, abs(controlsPeri->mutable_wheelmotors()->rightpower()));
    pwm->hardPWMChange(PWM_HARD_LEFT, abs(controlsPeri->mutable_wheelmotors()->leftpower()));
}
void PeripheralController::changeHandsPWM()
{
    pwm->softPWMChange(PWM_SOFT_RIGHT, abs(controlsPeri->mutable_handmotors()->rightpower()));
    pwm->softPWMChange(PWM_SOFT_LEFT, abs(controlsPeri->mutable_handmotors()->leftpower()));
}

void PeripheralController::writeRegisterData()
{
    registers->writeByte(leftOutRegisterToByte());
    registers->writeByte(rightOutRegisterToByte());
}

void PeripheralController::readRegisterData()
{

}


int PeripheralController::getWheelLeftAngle() const
{
    return wheelLeftAngle;
}
void PeripheralController::setWheelLeftAngle(int value)
{
    wheelLeftAngle = value;
}

int PeripheralController::getWheelRightAngle() const
{
    return wheelRightAngle;
}
void PeripheralController::setWheelRightAngle(int value)
{
    wheelRightAngle = value;
}

int PeripheralController::getHandLeftInternalAngle() const
{
    return handLeftInternalAngle;
}
void PeripheralController::setHandLeftInternalAngle(int value)
{
    handLeftInternalAngle = value;
}

int PeripheralController::getHandRightInternalAngle() const
{
    return handRightInternalAngle;
}
void PeripheralController::setHandRightInternalAngle(int value)
{
    handRightInternalAngle = value;
}

int PeripheralController::getHandLeftOuterAngle() const
{
    return handLeftOuterAngle;
}
void PeripheralController::setHandLeftOuterAngle(int value)
{
    handLeftOuterAngle = value;
}

int PeripheralController::getHandRightOuterAngle() const
{
    return handRightOuterAngle;
}
void PeripheralController::setHandRightOuterAngle(int value)
{
    handRightOuterAngle = value;
}
