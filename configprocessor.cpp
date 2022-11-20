#include "configprocessor.h"

/*!
  Constructor with custom config filename.
  \param[in] file Config filename.
*/
ConfigProcessor::ConfigProcessor(std::string configName):
    configName(configName)
{
    setOptionsConfig();
    readConfig(configName);
}

/*!
  Constructor with default config filename.
*/
ConfigProcessor::ConfigProcessor()
{
    configName = "amur.cfg";

    setOptionsConfig();
    readConfig(configName);
}

/*!
  Initialize libconfig.
\param[in] file Config filename.
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
  Read configuration from file.
  \param[in] file Config filename.
  \return 0 if success. 1 if I/O or parse error.
*/
int ConfigProcessor::readConfig(std::string configName)
{
    // Read the file. If there is an error, report it and exit.
    try
    {
      std::cout << "Reading config file: " << configName << std::endl;
      config.readFile(configName.c_str());
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
  Write configuration to file.
  \return 0 if success. 1 if I/O error.
*/
int ConfigProcessor::writeConfig()
{
    // Write out the updated configuration.
      try
      {
        config.writeFile(configName.c_str());
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
  Get string parameter from configuration.
  \param[in] settingName Address of parameter in configuration.
  \param[out] out Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::searchString(std::string settingName, std::string &out)
{
    // Lookup for name and version settings in configuration file.
    try
    {
      out = static_cast<std::string>( config.lookup(settingName).c_str() );
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No setting in configuration file: " << settingName << std::endl;
      return EXIT_FAILURE; // EXIT_FAILURE
    }
    return (EXIT_SUCCESS);
}

/*!
  Get integer parameter from configuration.
  \param[in] settingName Address of parameter in configuration.
  \param[out] out Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::searchInt(std::string settingName, int &out)
{
    // Lookup for name and version settings in configuration file.
    try
    {
      out = static_cast<int>(config.lookup(settingName));
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No setting in configuration file: " << settingName << std::endl;
      return EXIT_FAILURE; // EXIT_FAILURE
    }
    return (EXIT_SUCCESS);
}

/*!
  Get double parameter from configuration.
  \param[in] settingName Address of parameter in configuration.
  \param[out] out Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::searchDouble(std::string settingName, double &out)
{
    // Lookup for name and version settings in configuration file.
    try
    {
      out = static_cast<double>(config.lookup(settingName));
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No setting in configuration file: " << settingName << std::endl;
      return EXIT_FAILURE; // EXIT_FAILURE
    }
    return (EXIT_SUCCESS);
}

/*!
  Get bool parameter from configuration.
  param[in] settingName Address of parameter in configuration.
  \param[out] out Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::searchBool(std::string settingName, bool &out)
{
    // Lookup for name and version settings in configuration file.
    try
    {
      out = static_cast<bool>(config.lookup(settingName));
    }
    catch(const libconfig::SettingNotFoundException &nfex)
    {
      std::cerr << "No setting in configuration file: " << settingName << std::endl;
      return EXIT_FAILURE; // EXIT_FAILURE
    }
    return (EXIT_SUCCESS);
}

/*!
  Write string parameter to configuration.
  \param[in] settingName Address of parameter in configuration.
  \param[in] value Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::rewriteString(std::string settingName, std::string value)
{
    // Write parameter. If there is an error, report it and exit.
    try
    {
        libconfig::Setting &param = config.lookup(settingName);
        param = value;
    }
    // Inform user about IOException.
    catch(const libconfig::SettingNotFoundException &ex)
    {
      std::cerr << "Parameter not found!: " << settingName << std::endl;
      return(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/*!
  Write integer parameter to configuration.
  \param[in] settingName Address of parameter in configuration.
  \param[in] value Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::rewriteInt(std::string settingName, int value)
{
    // Write parameter. If there is an error, report it and exit.
    try
    {
        libconfig::Setting &param = config.lookup(settingName);
        param = value;
    }
    // Inform user about IOException.
    catch(const libconfig::SettingNotFoundException &ex)
    {
      std::cerr << "Parameter not found!: " << settingName << std::endl;
      return(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/*!
  Write double parameter to configuration.
  \param[in] settingName Address of parameter in configuration.
  \param[in] value Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::rewriteDouble(std::string settingName, double value)
{
    // Write parameter. If there is an error, report it and exit.
    try
    {
        libconfig::Setting &param = config.lookup(settingName);
        param = value;
    }
    // Inform user about IOException.
    catch(const libconfig::SettingNotFoundException &ex)
    {
      std::cerr << "Parameter not found!: " << settingName << std::endl;
      return(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/*!
  Write boolean parameter to configuration.
  \param[in] settingName Address of parameter in configuration.
  \param[in] value Value of parameter.
  \return Code of execution. Normal - 0, if file not found - 1.
*/
int ConfigProcessor::rewriteBool(std::string settingName, bool value)
{
    // Write parameter. If there is an error, report it and exit.
    try
    {
        libconfig::Setting &param = config.lookup(settingName);
        param = value;
    }
    // Inform user about IOException.
    catch(const libconfig::SettingNotFoundException &ex)
    {
      std::cerr << "Parameter not found!: " << settingName << std::endl;
      return(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

//int ConfigProcessor::addString(std::string settingName, std::string value)
//{
//    // TODO
//    return EXIT_SUCCESS;
//}

//int ConfigProcessor::addInt(std::string settingName, int value)
//{
//    // TODO
//    return EXIT_SUCCESS;
//}

//int ConfigProcessor::addDouble(std::string settingName, double value)
//{
//    // TODO
//    return EXIT_SUCCESS;
//}

//int ConfigProcessor::addBool(std::string settingName, bool value)
//{
//    // TODO
//    return EXIT_SUCCESS;
//}

/*!
  Return config filename.
*/
std::string ConfigProcessor::getConfigFilename() const
{
    return configName;
}

/*!
  Setup config filename.
*/
void ConfigProcessor::setConfigFilename(std::string newConfigName)
{
    configName = newConfigName;
}
