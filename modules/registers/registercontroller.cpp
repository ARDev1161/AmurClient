#include "registercontroller.h"

/*!
Создаёт экземпляр класса для работы с регистрами.
\param[in] outputPins Структура описывающая пины Raspberry Pi для подключения выходного регистра в нотации GPIO
\param[in] inputPins Структура описывающая пины Raspberry Pi для подключения входного регистра в нотации GPIO
*/
RegisterController::RegisterController
    (HC595Pins outputPins, HC165Pins inputPins)
{
    outputRegister = new HC595(outputPins);
    inputRegister = new HC165(inputPins);
}

RegisterController::~RegisterController()
{
    delete outputRegister;
    delete inputRegister;
}

/*!
Записывает байт данных в выходной регистр.
\param[in] writingByte Количество байтов, которые необходимо скопировать
*/
void RegisterController::writeByte(unsigned char writingByte)
{
    outputRegister->writeByte(writingByte);
}

/*!
Считывает байт данных из входного регистра.
\return byte Байт считанных данных
*/
unsigned char RegisterController::readByte()
{
    return inputRegister->readByte();
}

/*!
Отправляет сигнал регистрам для вывода данных на выходные пины.
*/
void RegisterController::refreshOutputData()
{
    outputRegister->latchSignal();
}

/*!
Отправляет сигнал регистрам для считывания данных с пинов во внутреннюю память регистров.
*/
void RegisterController::refreshInputData()
{
    inputRegister->loadRegister();
}

/*!
Отправляет сигнал включения регистрам.
*/
void RegisterController::enableRegisters()
{
    outputRegister->enable();
    inputRegister->enableClock();
}

/*!
Отправляет сигнал выключения регистрам.
*/
void RegisterController::disableRegisters()
{
    outputRegister->disable();
    inputRegister->disableClock();
}
