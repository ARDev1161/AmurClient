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
    registers->refreshInputData();

    unsigned char right = registers->readByte();
    unsigned char left = registers->readByte();

    parseBytesHC165(right, left);

    rightHC165 = right;
    leftHC165 = left;

    writeEncoderAngles();
}

void PeripheralController::parseBytesHC165(unsigned char right, unsigned char left)
{
    int signalA = 0;
    int signalB = 0;

    // Wheel left encoder: 5 & 6 bits in left register
    if ((left & 0x10) > (leftHC165 & 0x10)) signalA++; //A signal - 5 bit in left register
    if ((left & 0x20) > (leftHC165 & 0x20)) signalB++; //B signal - 6 bit in left register
    if(signalA > signalB) wheelLeftAngle++;
    if(signalA < signalB) wheelLeftAngle--;
    signalA = 0;
    signalB = 0;

    // Wheel right encoder: 7 & 8 bits in left register
    if ((left & 0x40) != (leftHC165 & 0x40)) signalB++; //B signal - 7 bit in left register
    if ((left & 0x80) != (leftHC165 & 0x80)) signalA++; //A signal - 8 bit in left register
    if(signalA > signalB) wheelRightAngle++;
    if(signalA < signalB) wheelRightAngle--;
    signalA = 0;
    signalB = 0;


    // Hand internal left encoder: 4 & 5 bits in right register
    if ((right & 0x08) > (rightHC165 & 0x08)) signalB++; //B signal - 4 bit in right register
    if ((right & 0x10) > (rightHC165 & 0x10)) signalA++; //A signal - 5 bit in right register
    if(signalA > signalB) wheelLeftAngle++;
    if(signalA < signalB) wheelLeftAngle--;
    signalA = 0;
    signalB = 0;

    // Hand internal right encoder: 2 & 7 bits in right register
    if ((right & 0x02) != (rightHC165 & 0x02)) signalB++; //B signal - 2 bit in right register
    if ((right & 0x40) != (rightHC165 & 0x40)) signalA++; //A signal - 7 bit in right register
    if(signalA > signalB) wheelRightAngle++;
    if(signalA < signalB) wheelRightAngle--;
    signalA = 0;
    signalB = 0;


    // Hand outer left encoder: 3 & 6 bits in right register
    if ((right & 0x04) > (rightHC165 & 0x04)) signalB++; //B signal - 3 bit in right register
    if ((right & 0x20) > (rightHC165 & 0x20)) signalA++; //A signal - 6 bit in right register
    if(signalA > signalB) wheelLeftAngle++;
    if(signalA < signalB) wheelLeftAngle--;
    signalA = 0;
    signalB = 0;

    // Hand outer right encoder: 1 & 8 bits in right register
    if ((right & 0x01) != (rightHC165 & 0x01)) signalB++; //B signal - 1 bit in right register
    if ((right & 0x80) != (rightHC165 & 0x80)) signalA++; //A signal - 8 bit in right register
    if(signalA > signalB) wheelRightAngle++;
    if(signalA < signalB) wheelRightAngle--;
    signalA = 0;
    signalB = 0;
}

void PeripheralController::writeEncoderAngles()
{
    // Write wheel left angle to protobuf
    if(wheelLeftAngle != 0){
        sensorsPeri->mutable_wheelencoders()->set_leftangle(wheelLeftAngle);
        wheelLeftAngle = 0;
    }

    // Write wheel right angle to protobuf
    if(wheelRightAngle != 0){
        sensorsPeri->mutable_wheelencoders()->set_rightangle(wheelRightAngle);
        wheelRightAngle = 0;
    }

    // Write hand internal left angle to protobuf
    if(handLeftInternalAngle != 0){
        sensorsPeri->mutable_handencoders()->set_leftinternalangle(handLeftInternalAngle);
        handLeftInternalAngle = 0;
    }

    // Write hand internal right angle to protobuf
    if(handRightInternalAngle != 0){
        sensorsPeri->mutable_handencoders()->set_rightinternalangle(handRightInternalAngle);
        handRightInternalAngle = 0;
    }

    // Write hand internal left angle to protobuf
    if(handLeftOuterAngle != 0){
        sensorsPeri->mutable_handencoders()->set_leftouterangle(handLeftInternalAngle);
        handLeftOuterAngle = 0;
    }

    // Write hand internal right angle to protobuf
    if(handRightOuterAngle != 0){
        sensorsPeri->mutable_handencoders()->set_leftouterangle(handRightInternalAngle);
        handRightOuterAngle = 0;
    }
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
