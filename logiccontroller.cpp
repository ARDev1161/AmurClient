#include "logiccontroller.h"

/*!
Создаёт экземпляр класса логики управления роботом.
*/
LogicController::LogicController()
{
    config = new ConfigProcessor();
    printHeadInfo();

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

    delete periphery;
    delete network;

    delete sensors;
    delete controls;

    delete config;
    delete configName;
}

/*!
  Функция печати основной информации о программе
*/
void LogicController::printHeadInfo()
{
    std::cout << "AmurClient VERSION - " << config->configSearchString("version") << std::endl;
    std::cout << "IP address: " << config->configSearchString("Amur.Network.address") << std::endl;
    std::cout << "Pi = " << config->configSearchDouble("Amur.misc.pi") << std::endl;
    std::cout << "FPS = " << config->configSearchInt("Amur.gstreamer.fps") << std::endl << std::endl;
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
