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
    logicTimer.start(10000000); // 10 milliseconds

    std::this_thread::sleep_for(std::chrono::milliseconds(100));// Wait 0.1 second
}

/*!
  Функция таймера, вызывает проверку активности подключения к серверу. Если соединение неактивно, то инициирует его.
*/
void LogicController::run()
{
    if(network->checkAlive()){

        std::string controlsSerialized;
        controls->SerializeToString(&controlsSerialized);

//        sensors->mutable_temperature()->set_tempcpu(42);
//        sensors->mutable_temperature()->set_temppressure(20);

        if(controlsSerialized != controlsPrev){
            sendBuffer();
            controlsPrev = controlsSerialized;
        }

        recvBuffer();

        peripheryUpdate();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));// Wait 10 milliseconds
    }
    else{
        connectToServer();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));// Wait connecting
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
