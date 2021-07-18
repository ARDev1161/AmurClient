#include "configprocessor.h"

ConfigProcessor::ConfigProcessor(const char *configName):
    configName(configName)
{
    setOptionsConfig();
    readConfig(configName);
}

ConfigProcessor::ConfigProcessor()
{
    configName = "amur.cfg";

    setOptionsConfig();
    readConfig(configName);
}

/*!
  Инициализация libconfig.
\param[in] file Имя файла конфигурации.
*/
int ConfigProcessor::setOptionsConfig()
{
//    config.setOptions(libconfig::Config::OptionFsync
//                | libconfig::Config::OptionSemicolonSeparators
//                | libconfig::Config::OptionColonAssignmentForGroups
//                | libconfig::Config::OptionOpenBraceOnSeparateLine);

    return (EXIT_SUCCESS);
}

/*!
  Чтение параметров конфигурации из config файла.
\param[in] file Имя файла конфигурации.
*/
int ConfigProcessor::readConfig(const char *configName)
{
    // Read the file. If there is an error, report it and exit.
    try
    {
      std::cout << "Reading config file: " << configName << std::endl;
      config.readFile(configName);
    }
    // Inform user about IOException.
    catch(const libconfig::FileIOException &fioex)
    {
      std::cerr << "I/O error while reading config file." << std::endl;
      return(EXIT_FAILURE);
    }
    // Inform user about the parse exception.
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
int ConfigProcessor::writeConfig(const char *configName)
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
std::string ConfigProcessor::configSearchString(const char *settingName)
{
    // Lookup for name and version settings in configuration file.
    try
    {
      return config.lookup(settingName);
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No setting in configuration file: " << settingName << std::endl;
      return 0; // EXIT_FAILURE
    }
}

int ConfigProcessor::configSearchInt(const char *settingName)
{
    // Lookup for name and version settings in configuration file.
    try
    {
      return config.lookup(settingName);
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No setting in configuration file: " << settingName << std::endl;
      return 0; // EXIT_FAILURE
    }
}

double ConfigProcessor::configSearchDouble(const char *settingName)
{
    // Lookup for name and version settings in configuration file.
    try
    {
      return config.lookup(settingName);
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No setting in configuration file: " << settingName << std::endl;
      return 0; // EXIT_FAILURE
    }
}


/*!
  Возвращает имя конфигурационного файла.
*/
const char *ConfigProcessor::getConfigFilename() const
{
    return configName;
}

/*!
  Изменяет имя конфигурационного файла.
*/
void ConfigProcessor::setConfigFilename(const char *newConfigName)
{
    configName = newConfigName;
}
