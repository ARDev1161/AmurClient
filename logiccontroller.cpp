#include "logiccontroller.h"

/*!
Создаёт экземпляр класса логики управления роботом.
*/
LogicController::LogicController()
{
    controls = new AMUR::AmurControls();
    sensors = new AMUR::AmurSensors();
    periphery = new PeripheralController(controls, sensors);
    network = new NetworkController(controls, sensors);

    initTimer();
}

LogicController::~LogicController()
{
    delete sensors;
    delete controls;

    delete periphery;
    delete network;
}

/*!
Создаёт экземпляр класса для работы с периферическим оборудованием.
*/
void LogicController::initTimer()
{
    logicTimer.registerEventRunnable(*this);
    logicTimer.start(10000000); // 10 milliseconds

    std::this_thread::sleep_for(std::chrono::milliseconds(100));// Wait 0.1 second
}

/*!
  Функция таймера, вызывает проверку активности подключения к серверу. Если соединение неактивно, то инициирует его.
*/
void LogicController::run()
{
    if( controls->DebugString() == controlsPrev.DebugString() )
        std::this_thread::sleep_for(std::chrono::milliseconds(10));// Wait 10 milliseconds

    peripheryUpdate();
    controlsPrev = *controls;
}

/*!
  Инициирует подключение к серверу.
\param[in] host Адрес сервера
\param[in] port Порт сервера
*/
void LogicController::connectToServer(std::string host, unsigned int port)
{
    this->host = host;
    this->port =port;

    network->runClient(host, port);
}

/*!
  Инициирует подключение к серверу с адресом и портом по умолчанию.
*/
void LogicController::connectToServer()
{
    network->runClient("0.0.0.0", 7777);
}

/*!
  Обновляет данные периферического оборудования.
*/
void LogicController::peripheryUpdate()
{
    periphery->updateData();
}
