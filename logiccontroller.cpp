#include "logiccontroller.h"

/*!
Создаёт экземпляр класса логики управления роботом.
*/
LogicController::LogicController()
{
    controls = new AmurControls();
    sensors = new AmurSensors();
    periphery = new PeripheralController(controls, sensors);
    network = new NetworkController(controls, sensors, host, port);

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
    logicTimer.start(42000000); // 42 milliseconds

    std::this_thread::sleep_for(std::chrono::seconds(1));// Wait 1 second
}

/*!
  Функция таймера, вызывает проверку активности подключения к серверу. Если соединение неактивно, то инициирует его.
*/
void LogicController::run()
{
    if(network->checkAlive()){
        sendBuffer();
        recvBuffer();

        peripheryUpdate();
    }
    else{
        connectToServer();
    }
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

    network->connect(host, port);
}

/*!
  Инициирует подключение к серверу с адресом и портом по умолчанию.
*/
void LogicController::connectToServer()
{
    network->connect();
}

/*!
  Принимает сериализованный буфер управления с сервера.
*/
void LogicController::recvBuffer()
{
    network->recvBufferAsString();
}

/*!
  Отправляет сериализованный буфер сенсоров на сервер.
*/
void LogicController::sendBuffer()
{
    network->sendBufferAsString();
}

/*!
  Обновляет данные периферического оборудования.
*/
void LogicController::peripheryUpdate()
{
    periphery->updateData();
}
