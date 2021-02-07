#include "peripheralcontroller.h"

/*!
Создаёт экземпляр класса для работы с периферическим оборудованием.
\param[in] *controls Указатель на protobuf буффер AmurControls
\param[in] *sensors Указатель на protobuf буффер AmurSensors
*/
PeripheralController::PeripheralController(AMUR::AmurControls *controls, AMUR::AmurSensors *sensors):
     sensorsPeri(sensors), controlsPeri(controls)
{
    pigpioInit();

    registers = new RegisterController(settings.outputRegisters,
                                       settings.inputRegisters);
    pwm = new PWMController();
    initPWM();

    initTimer();
}

PeripheralController::~PeripheralController()
{
    peripheralTimer.stop();

    sensorsPeri = nullptr;
    controlsPeri = nullptr;

    delete registers;
    delete pwm;
}

/*!
Функция таймера, вызывает проверку времени работы моторов.
*/
void PeripheralController::run()
{
    checkMotorsTime();
}

/*!
Функция для обновления данных регистров и сигналов PWM.
*/
void PeripheralController::updateData()
{
    // Update output registers data & input registers buffers
    writeRegisterData();
    readRegisterData();

    // Update PWM values
    changeWheelsPWM();
    changeHandsPWM();
}

/*!
Функция настройки и запуска таймера.
*/
void PeripheralController::initTimer()
{
    peripheralTimer.registerEventRunnable(*this);
    peripheralTimer.start(10000000); // 10 milliseconds
}

/*!
Инициализирует библиотеку pigpio
*/
void PeripheralController::pigpioInit()
{
#if __has_include(<pigpio.h>)
    int code;
    if((code = gpioInitialise()) < 0) //setup GPIO, this uses actual BCM pin numbers
    {
        std::cout << "pigpioInit failed!!! : Error - " << code << std::endl;
        abort();
    }
    else
        std::cout << "pigpioInit successed! " << std::endl;
#else
    std::cout << "pigpio not installed !!!" << std::endl;
#endif
}

/*!
Инициализирует программные и аппаратные PWM сигналы указанные в структуре настроек экземпляра класса.
*/
void PeripheralController::initPWM()
{
    // Setup hardware PWM for wheel motors
    pwm->hardPWMCreate( settings.pwm.wheelRightPin );
    pwm->hardPWMCreate( settings.pwm.wheelLeftPin );

    // Setup software PWM for hand motors
    pwm->softPWMCreate( settings.pwm.handRightPin );
    pwm->softPWMCreate( settings.pwm.handLeftPin );
}

/*!
Собирает байт данных для записи в левый регистр из protobuf буфера.
\return Байт данных для записи в левый выходной регистр
*/
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

/*!
Собирает байт данных для записи в правый регистр из protobuf буфера.
\return Байт данных для записи в правый выходной регистр
*/
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

/*!
Изменяет скважность PWM сигналов управляющих моторами гусениц на данные из protobuf буфера.
*/
void PeripheralController::changeWheelsPWM()
{
    if(prevRightWheelPWM != abs(controlsPeri->mutable_wheelmotors()->rightpower()))
        pwm->hardPWMChange( settings.pwm.wheelRightPin, abs(controlsPeri->mutable_wheelmotors()->rightpower()) );

    if(prevLeftWheelPWM != abs(controlsPeri->mutable_wheelmotors()->leftpower()))
        pwm->hardPWMChange( settings.pwm.wheelLeftPin, abs(controlsPeri->mutable_wheelmotors()->leftpower()) );
}

/*!
Изменяет скважность PWM сигналов управляющих моторами манипулятора на данные из protobuf буфера.
*/
void PeripheralController::changeHandsPWM()
{
    if(prevRightHandPWM != abs(controlsPeri->mutable_handmotors()->rightpower()))
        pwm->softPWMChange( settings.pwm.handRightPin, abs(controlsPeri->mutable_handmotors()->rightpower()) );

    if(prevLeftHandPWM != abs(controlsPeri->mutable_handmotors()->leftpower()))
        pwm->softPWMChange( settings.pwm.handLeftPin, abs(controlsPeri->mutable_handmotors()->leftpower()) );
}

/*!
Записывает данные в выходные регистры.
*/
void PeripheralController::writeRegisterData() // Read data from protobuf & write to HC595
{
    unsigned char leftRegister = leftOutRegisterToByte();
    unsigned char rightRegister = rightOutRegisterToByte();

    if((prevLeftHC595 != leftRegister)||(prevRightHC595 != rightRegister)){

        registers->writeByte(leftRegister); // Write left byte to HC595
        registers->writeByte(rightRegister); // Write right byte to HC595

        registers->refreshOutputData(); // Load data (latch pulse)
    }
}

/*!
  Считывает данные из входных регистров.
*/
void PeripheralController::readRegisterData() // Read data from HC165 & write to protobuf
{
    registers->refreshInputData(); // Load data (latch pulse)

    unsigned char right = registers->readByte(); // Read right byte from HC165
    unsigned char left = registers->readByte(); // Read left byte from HC165

    if((prevRightHC165 != right) || (prevLeftHC165 != left))
    {
        parseBytesHC165(right, left); // Parse bytes on angles

        prevRightHC165 = right; // Write prev bytes
        prevLeftHC165 = left; // Write prev bytes

        writeEncodersAngles(); // Write angles
    }
}

/*!
  Получает изменение угла поворота мотора по энкодеру.
  \param[out] *angle Указатель на переменную хранящую угол для мотора
  \param[in] addrA Адрес входа A энкодера на входном регистре, в адресе пин указан битом в байте.
  \param[in] addrB Адрес входа B энкодера на входном регистре, в адресе пин указан битом в байте.
  \param[in] byte Байт данных считанный из входного регистра
  \param[in] previousByte Предыдущий байт данных считанный из входного регистра
*/
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

/*!
  Преобразует данные всех энкодеров моторов в изменения углов.
  \param[in] right Байт данных считанный из правого входного регистра
  \param[in] left Байт данных считанный из левого входного регистра
*/
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

/*!
  Записывает углы моторов в protobuf буффер.
*/
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

/*!
  Проверяет время работы моторов по значениям из protobuf буффера, по достижению времени менее 10мс отключает конкретный мотор.
*/
void PeripheralController::checkMotorsTime()
{
    int changes = 0;

    if(controlsPeri->mutable_wheelmotors()->lefttime() >= 10)
        controlsPeri->mutable_wheelmotors()->set_lefttime( controlsPeri->mutable_wheelmotors()->lefttime() - 10);
    else {
        if(controlsPeri->mutable_wheelmotors()->lefttime() > 0)
        {
            controlsPeri->mutable_wheelmotors()->set_leftpower(0);
            controlsPeri->mutable_wheelmotors()->set_lefttime(0);

            changes++;
        }
    }

    if(controlsPeri->mutable_wheelmotors()->righttime() >= 10)
        controlsPeri->mutable_wheelmotors()->set_righttime( controlsPeri->mutable_wheelmotors()->righttime() - 10);
    else  {
        if(controlsPeri->mutable_wheelmotors()->righttime() > 0)
        {
            controlsPeri->mutable_wheelmotors()->set_rightpower(0);
            controlsPeri->mutable_wheelmotors()->set_righttime(0);

            changes++;
        }
    }


    if(controlsPeri->mutable_handmotors()->lefttime() >= 10)
        controlsPeri->mutable_handmotors()->set_lefttime( controlsPeri->mutable_handmotors()->lefttime() - 10);
    else  {
        if(controlsPeri->mutable_handmotors()->lefttime() > 0)
        {
            controlsPeri->mutable_handmotors()->set_leftpower(0);
            controlsPeri->mutable_handmotors()->set_lefttime(0);

            changes++;
        }
    }

    if(controlsPeri->mutable_handmotors()->righttime() >= 10)
        controlsPeri->mutable_handmotors()->set_righttime( controlsPeri->mutable_handmotors()->righttime() - 10);
    else {
        if(controlsPeri->mutable_handmotors()->righttime() > 0)
        {
            controlsPeri->mutable_handmotors()->set_rightpower(0);
            controlsPeri->mutable_handmotors()->set_righttime(0);

            changes++;
        }
    }

    if(changes > 0) updateData();
}
