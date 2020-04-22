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

PeripheralController::~PeripheralController()
{
    sensorsPeri = nullptr;
    controlsPeri = nullptr;

    delete registers;
    delete pwm;
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
    // Setup hardware PWM for wheel motors
    pwm->hardPWMCreate(PWM_HARD_RIGHT);
    pwm->hardPWMCreate(PWM_HARD_LEFT);

    // Setup software PWM for hand motors
    pwm->softPWMCreate(PWM_SOFT_RIGHT);
    pwm->softPWMCreate(PWM_SOFT_LEFT);
}

unsigned char PeripheralController::leftOutRegisterToByte()
{
    unsigned char byte = 0x00;

    // left LED light input
    byte |= (controlsPeri->mutable_light()->ledleftpower() > 0);
    byte <<=1;

    // enable input: wheel left motor
    byte |= ( abs(controlsPeri->mutable_wheelmotors()->leftpower()) > 0);
    byte <<=1;

    // enable input: hand left motor
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

    return byte;
}
unsigned char PeripheralController::rightOutRegisterToByte()
{
    unsigned char byte = 0x00;

    // right LED light input
    byte |= (controlsPeri->mutable_light()->ledrightpower() > 0);
    byte <<=1;

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

void PeripheralController::writeRegisterData() // Read data from protobuf & write to HC595
{
    registers->writeByte(leftOutRegisterToByte()); // Write left byte to HC595
    registers->writeByte(rightOutRegisterToByte()); // Write right byte to HC595

    registers->refreshOutputData(); // Load data (latch pulse)
}

void PeripheralController::readRegisterData() // Read data from HC165 & write to protobuf
{
    registers->refreshInputData(); // Load data (latch pulse)

    unsigned char right = registers->readByte(); // Read right byte from HC165
    unsigned char left = registers->readByte(); // Read left byte from HC165

    parseBytesHC165(right, left);

    prevRightHC165 = right;
    prevLeftHC165 = left;

    writeEncodersAngles();
}

inline void PeripheralController::getChangeEncoderAngle
(unsigned char addrA, unsigned char addrB, unsigned char const byte,  unsigned char const previousByte, int *const angle)
{
    int signalA = 0;
    int signalB = 0;

    // encoder: addrA & addrB bits in left register
    if ((byte & addrA) > (previousByte & addrA)) signalA++; //A signal in register
    if ((byte & addrB) > (previousByte & addrB)) signalB++; //B signal in register
    if(signalA > signalB) (*angle)++;
    if(signalA < signalB) (*angle)--;
}

void PeripheralController::parseBytesHC165(unsigned char right, unsigned char left)
{
    // Wheel left encoder: 5(A) - 0x10 & 6(B) - 0x20 bits in left register
    getChangeEncoderAngle(0x10, 0x20, left, prevLeftHC165, &wheelLeftAngle);

    // Wheel right encoder: 8(A) - 0x80 & 7(B) - 0x40 bits in left register
    getChangeEncoderAngle(0x80, 0x40, left, prevLeftHC165, &wheelRightAngle);

    // Hand internal left encoder: 5(A) - 0x10 & 4(B) - 0x08 bits in right register
    getChangeEncoderAngle(0x10, 0x08, right, prevRightHC165, &handLeftInternalAngle);

    // Hand internal right encoder: 7(A) - 0x40 & 2(B) - 0x02 bits in right register
    getChangeEncoderAngle(0x40, 0x02, right, prevRightHC165, &handRightInternalAngle);

    // Hand outer left encoder: 6(A) - 0x20 & 3(B) - 0x04 bits in right register
    getChangeEncoderAngle(0x20, 0x04, right, prevRightHC165, &handLeftOuterAngle);

    // Hand outer right encoder: 8(A) - 0x80 & 1(B) - 0x01 bits in right register
    getChangeEncoderAngle(0x80, 0x01, right, prevRightHC165, &handRightOuterAngle);
}

void PeripheralController::writeEncodersAngles()
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
