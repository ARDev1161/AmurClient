#include "configprocessor.h"

/*!
  Constructor with custom config filename
  \param[in] file Config filename
*/
ConfigProcessor::ConfigProcessor(const std::string &configName)
    : configName(configName) {
  setOptionsConfig();
  readConfig(configName);
}

/*!
  Initialize libconfig
\param[in] file Config filename
*/
int ConfigProcessor::setOptionsConfig() {
  //    config.setOptions(libconfig::Config::OptionFsync
  //                | libconfig::Config::OptionSemicolonSeparators
  //                | libconfig::Config::OptionColonAssignmentForGroups
  //                | libconfig::Config::OptionOpenBraceOnSeparateLine);

  return (EXIT_SUCCESS);
}

/*!
  Read configuration from file
  \param[in] file Config filename
  \return 0 if success. 1 if I/O or parse error
*/
int ConfigProcessor::readConfig(const std::string &configName) {
  // Read the file. If there is an error, report it and exit.
  try {
    std::clog << "Reading config file: " << configName << std::endl;
    config.readFile(configName.c_str());
  }
  // Inform user about IOException.
  catch (const libconfig::FileIOException &fioex) {
    std::cerr << "I/O error while reading config file!!! -> " << configName
              << std::endl;
    return (EXIT_FAILURE);
  }
  // Inform user about the parse exception.
  catch (const libconfig::ParseException &pex) {
    std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
              << " - " << pex.getError() << std::endl;
    return (EXIT_FAILURE);
  }

  return (EXIT_SUCCESS);
}

int ConfigProcessor::readConfig()
{
  return readConfig(configName);
}

/*!
  Write configuration to file
  \return 0 if success. 1 if I/O error
*/
int ConfigProcessor::writeConfig() {
  // Write out the updated configuration.
  try {
    config.writeFile(configName.c_str());
    std::clog << "Configuration successfully written to: " << configName
              << std::endl;
  } catch (const libconfig::FileIOException &fioex) {
    std::cerr << "I/O error while writing file: " << configName << std::endl;
    return (EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}

/*!
  Get type of parameter from configuration
  \param[in] settingName Address of parameter in configuration
  \return Type of parameter. If parameter not found -
  libconfig::Setting::TypeNone
*/
libconfig::Setting::Type ConfigProcessor::getType(std::string settingName) {
  if(settingName.empty())
    return libconfig::Setting::TypeNone;

  if (!config.exists(settingName)) {
    std::cerr << "Parameter not found! - " << settingName << std::endl;
    return libconfig::Setting::TypeNone;
  }

  libconfig::Setting &setting = config.lookup(settingName);
  return setting.getType();
}

/*!
  Check is scalar parameter
  \param[in] settingName Address of parameter in configuration
  \return True if scalar, False if not
*/
bool ConfigProcessor::isScalar(std::string settingName) {
  if(settingName.empty())
    return false;
  if (!config.exists(settingName)) {
    std::cerr << "Parameter not found! - " << settingName << std::endl;
    return false;
  }

  libconfig::Setting &setting = config.lookup(settingName);
  return setting.isScalar();
}

/*!
  Check is number parameter
  \param[in] settingName Address of parameter in configuration
  \return True if number, False if not
*/
bool ConfigProcessor::isNumber(std::string settingName) {
  if(settingName.empty())
    return false;
  if (!config.exists(settingName)) {
    std::cerr << "Parameter not found! - " << settingName << std::endl;
    return false;
  }

  libconfig::Setting &setting = config.lookup(settingName);
  return setting.isNumber();
}

/*!
  Check is aggregate parameter
  \param[in] settingName Address of parameter in configuration
  \return True if aggregate, False if not
*/
bool ConfigProcessor::isAggregate(std::string settingName) {
  if(settingName.empty())
    return false;
  if (!config.exists(settingName)) {
    std::cerr << "Parameter not found! - " << settingName << std::endl;
    return false;
  }

  libconfig::Setting &setting = config.lookup(settingName);
  return setting.isAggregate();
}

/*!
  Get string parameter from configuration
  \param[in] settingName Address of parameter in configuration
  \param[out] out Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::searchString(std::string settingName, std::string &out) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    out = static_cast<std::string>(config.lookup(settingName).c_str());
  } catch (const libconfig::SettingNotFoundException &nfex) {
    std::cerr << "No setting in configuration file: " << settingName
              << std::endl;
    return EXIT_FAILURE; // EXIT_FAILURE
  }
  return (EXIT_SUCCESS);
}

/*!
  Get integer parameter from configuration
  \param[in] settingName Address of parameter in configuration
  \param[out] out Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::searchInt(std::string settingName, int &out) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    out = static_cast<int>(config.lookup(settingName));
  } catch (const libconfig::SettingNotFoundException &nfex) {
    std::cerr << "No setting in configuration file: " << settingName
              << std::endl;
    return EXIT_FAILURE; // EXIT_FAILURE
  }
  return (EXIT_SUCCESS);
}

/*!
  Get double parameter from configuration
  \param[in] settingName Address of parameter in configuration
  \param[out] out Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::searchFloat(std::string settingName, float &out) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    out = static_cast<float>(config.lookup(settingName));
  } catch (const libconfig::SettingNotFoundException &nfex) {
    std::cerr << "No setting in configuration file: " << settingName
              << std::endl;
    return EXIT_FAILURE; // EXIT_FAILURE
  }
  return (EXIT_SUCCESS);
}

/*!
  Get bool parameter from configuration
  param[in] settingName Address of parameter in configuration
  \param[out] out Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::searchBool(std::string settingName, bool &out) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    out = static_cast<bool>(config.lookup(settingName));
  } catch (const libconfig::SettingNotFoundException &nfex) {
    std::cerr << "No setting in configuration file: " << settingName
              << std::endl;
    return EXIT_FAILURE; // EXIT_FAILURE
  }
  return (EXIT_SUCCESS);
}

/*!
  Write string parameter to configuration
  \param[in] settingName Address of parameter in configuration
  \param[in] value Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::rewriteString(std::string settingName,
                                   const std::string &value) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    libconfig::Setting &param = config.lookup(settingName);
    param = value;
  }
  // Inform user about IOException.
  catch (const libconfig::SettingNotFoundException &ex) {
    std::cerr << "Parameter not found!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  } catch (const libconfig::SettingTypeException &ex) {
    std::cerr << "Type is wrong!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

/*!
  Write integer parameter to configuration
  \param[in] settingName Address of parameter in configuration
  \param[in] value Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::rewriteInt(std::string settingName, int value) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    libconfig::Setting &param = config.lookup(settingName);
    param = value;
  }
  // Inform user about IOException
  catch (const libconfig::SettingNotFoundException &ex) {
    std::cerr << "Parameter not found!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  } catch (const libconfig::SettingTypeException &ex) {
    std::cerr << "Type is wrong!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

/*!
  Write double parameter to configuration
  \param[in] settingName Address of parameter in configuration
  \param[in] value Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::rewriteFloat(std::string settingName, float value) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    libconfig::Setting &param = config.lookup(settingName);
    param = value;
  }
  // Inform user about IOException
  catch (const libconfig::SettingNotFoundException &ex) {
    std::cerr << "Parameter not found!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  } catch (const libconfig::SettingTypeException &ex) {
    std::cerr << "Type is wrong!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

/*!
  Write boolean parameter to configuration
  \param[in] settingName Address of parameter in configuration
  \param[in] value Value of parameter
  \return Code of execution. Normal - 0, if file not found - 1
*/
int ConfigProcessor::rewriteBool(std::string settingName, bool value) {
  if(settingName.empty())
    return EXIT_FAILURE;

  try {
    libconfig::Setting &param = config.lookup(settingName);
    param = value;
  }
  // Inform user about IOException
  catch (const libconfig::SettingNotFoundException &ex) {
    std::cerr << "Parameter not found!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  } catch (const libconfig::SettingTypeException &ex) {
    std::cerr << "Type is wrong!: " << settingName << std::endl;
    return (EXIT_FAILURE);
  }
  return EXIT_SUCCESS;
}

// int ConfigProcessor::addString(std::string settingName, std::string value)
//{
//     // TODO
//     return EXIT_SUCCESS;
// }

// int ConfigProcessor::addInt(std::string settingName, int value)
//{
//     // TODO
//     return EXIT_SUCCESS;
// }

// int ConfigProcessor::addFloat(std::string settingName, float value)
//{
//     // TODO
//     return EXIT_SUCCESS;
// }

// int ConfigProcessor::addBool(std::string settingName, bool value)
//{
//     // TODO
//     return EXIT_SUCCESS;
// }

/*!
  Return config filename
*/
std::string ConfigProcessor::getConfigFilename() const { return configName; }

/*!
  Setup config filename
*/
void ConfigProcessor::setConfigFilename(const std::string &newConfigName) {
  configName = newConfigName;
}
