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

    network->runClient(address);
    controls->mutable_wheelmotors()->set_leftpower(42);
    controls->mutable_wheelmotors()->set_lefttime(420);
    controls->mutable_wheelmotors()->set_rightpower(42);
    controls->mutable_wheelmotors()->set_righttime(420);

    controls->mutable_handmotors()->set_leftpower(42);
    controls->mutable_handmotors()->set_rightpower(42);
    controls->mutable_handmotors()->set_lefttime(420);
    controls->mutable_handmotors()->set_righttime(42);

    worker();
}

LogicController::~LogicController()
{
    std::cout << "Close LogicController... " << std::endl;
    delete sensors;
    delete controls;

    delete periphery;
    delete network;
}

/*!
  Главный цикл
*/
void LogicController::worker()
{
    while(!workerStopped)
    {
        if( controls->DebugString() != controlsPrev.DebugString() )
        {
            periphery->updateData();
            controlsPrev = *controls;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Wait 10 milliseconds
    }
}

/*!
  Инициирует подключение к серверу.
\param[in] host Адрес сервера
\param[in] port Порт сервера
*/
void LogicController::connectToServer(std::string host, unsigned int port)
{
    this->address = host + ":" + std::to_string(port);
    connectToServer();
}

/*!
  Инициирует подключение к серверу с адресом и портом по умолчанию.
*/
void LogicController::connectToServer()
{
    network->runClient(address);
}

