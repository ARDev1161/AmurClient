#include "registercontroller.h"

/*!
Создаёт экземпляр класса для работы с регистрами.
\param[in] outputPins Структура описывающая пины Raspberry Pi для подключения выходного регистра в нотации GPIO
*/
RegisterController::RegisterController(RegisterSettings *settings):
registerSettings(settings)
{
    outputRegister = new HC595(registerSettings);
    inputRegister = new HC165(registerSettings);
}

/*!
Создаёт экземпляр класса для работы с регистрами c отдельной копией настроек по умолчанию.
*/
RegisterController::RegisterController()
{
    registerSettings = new RegisterSettings();
    outputRegister = new HC595(registerSettings);
    inputRegister = new HC165(registerSettings);
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
