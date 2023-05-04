#include "logiccontroller.h"

/*!
Создаёт экземпляр класса логики управления роботом.
*/
LogicController::LogicController()
{
    config = new ConfigProcessor(configName); // Load config file
    fillFieldsByConfig(); // Fill fields by config file
    printVersion(); // Print info about current AmurClient configuration

    periphery = new PeripheralController(&controls, &sensors);
    network = new NetworkController(&controls, &sensors);
    network->startArpingService(bcastPort, arpingPort);

    connectToServer();
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
  Функция проверяющая и заполняющая значения полей из конфиг файла
*/
void LogicController::fillFieldsByConfig()
{
    std::string ip ;
    int result = config->searchString("Amur.Network.address", ip);
    if(ip != ""){
        this->address = ip;
    }
}

/*!
  Функция печати версии программы
*/
int LogicController::printVersion()
{
    std::string version;
    if(config->searchString("version", version) == 0)
        std::cout << "Version: " << version << std::endl;
    else
        return -1;

    return 0;
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
    if(address == ""){
        std::cout << "No IP in config. Wait answer from server..." << std::endl;
        while(true){
            if(network->runClient() == 0){
                std::cout << "Connected" << std::endl;
                network->stopArpingService();
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Wait 10 milliseconds
        }
    }
    else{
        network->runClient(address);
    }

}
