#include "logiccontroller.h"

/*!
Создаёт экземпляр класса логики управления роботом.
*/
LogicController::LogicController()
{
    config = new ConfigProcessor();
    printHeadInfo();

    periphery = new PeripheralController(&controls, &sensors);
    network = new NetworkController(&controls, &sensors);

    network->runClient(address);
    worker();
}

LogicController::~LogicController()
{
    std::cout << "Close LogicController... " << std::endl;

    delete periphery;
    delete network;

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
//        std::string s2 = controlsPrev.DebugString();
//        std::string s1 = controls.DebugString();

//        std::string s4 = controlsPrev.SerializeAsString();
//        std::string s3 = controls.SerializeAsString();
//        if( s1 != s2 )
        {
            periphery->updateData();
            controlsPrev = controls;
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
