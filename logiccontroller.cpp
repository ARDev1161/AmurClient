#include "logiccontroller.h"

/*!
Создаёт экземпляр класса логики управления роботом.
*/
LogicController::LogicController()
{
    setOptionsConfig(configName);
    readConfig(configName);

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

    delete configName;
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
  Инициализация libconfig.
\param[in] file Имя файла конфигурации.
*/
int LogicController::setOptionsConfig(const char *configName)
{
    config.setOptions(libconfig::Config::OptionFsync
                | libconfig::Config::OptionSemicolonSeparators
                | libconfig::Config::OptionColonAssignmentForGroups
                | libconfig::Config::OptionOpenBraceOnSeparateLine);

    return (EXIT_SUCCESS);
}

/*!
  Чтение параметров конфигурации из config файла.
\param[in] file Имя файла конфигурации.
*/
int LogicController::readConfig(const char *configName)
{
    // Read the file. If there is an error, report it and exit.
    try
    {
      std::cout << "Reading config file: " << configName << std::endl;
      config.readFile(configName);
    }

    catch(const libconfig::FileIOException &fioex)
    {
      std::cerr << "I/O error while reading config file." << std::endl;
      return(EXIT_FAILURE);
    }

    catch(const libconfig::ParseException &pex)
    {
      std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                << " - " << pex.getError() << std::endl;
      return(EXIT_FAILURE);
    }

    return (EXIT_SUCCESS);
}

/*!
  Запись параметров конфигурации в config файл.
\param[in] file Имя файла конфигурации.
*/
int LogicController::writeConfig(const char *configName)
{
    // Write out the updated configuration.
      try
      {
        config.writeFile(configName);
        std::cerr << "Configuration successfully written to: " << configName << std::endl;

      }
      catch(const libconfig::FileIOException &fioex)
      {
        std::cerr << "I/O error while writing file: " << configName << std::endl;
        return(EXIT_FAILURE);
      }
    return (EXIT_SUCCESS);
}

/*!
  Поиск настройки в конфигурационном файле по имени.
\param[in] file Имя настройки в конфигурационном файле.
*/
int LogicController::configSearch(const char *settingName)
{
    // Получить некое название.
    try
    {
      std::string name = config.lookup(settingName);
      std::cout << "Store name: " << name << std::endl << std::endl;
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No 'name' setting in configuration file." << std::endl;
    }

//    const libconfig::Setting& root = config.getRoot();

//    if(! root.exists("inventory"))
//        root.add("inventory", libconfig::Setting::TypeGroup);

//    libconfig::Setting &inventory = root["inventory"];

//    if(! inventory.exists("movies"))
//        inventory.add("movies", libconfig::Setting::TypeList);

//      libconfig::Setting &movies = inventory["movies"];

//      // Create the new movie entry.
//      libconfig::Setting &movie = movies.add(libconfig::Setting::TypeGroup);

//      movie.add("media", libconfig::Setting::TypeString) = "DVD";

    return (EXIT_SUCCESS);
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

/*!
  Возвращает имя конфигурационного файла.
*/
const char *LogicController::getConfigFilename() const
{
    return configName;
}

/*!
  Изменяет имя конфигурационного файла.
*/
void LogicController::setConfigFilename(const char *newConfigName)
{
    configName = newConfigName;
}

