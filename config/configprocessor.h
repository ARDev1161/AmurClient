#ifndef CONFIGPROCESSOR_H
#define CONFIGPROCESSOR_H

#include <iostream>
#include <libconfig.h++>
#include <vector>

#if ((LIBCONFIGXX_VER_MAJOR == 1) && (LIBCONFIGXX_VER_MINOR >= 4))
// use features, existed in libconfig 1.4 or newer
#endif

class ConfigProcessor {
  // libconfig settings
  std::string configName;   ///< Setuped config filename
  libconfig::Config config; ///< Libconfig instance

  std::vector<std::string> splitPath(std::string path);

public:
  explicit ConfigProcessor(const std::string &configName = "");

  static int setOptionsConfig();
  int readConfig(const std::string &configName);
  int readConfig();
  int writeConfig();

  libconfig::Setting::Type getType(std::string settingName);
  bool isScalar(std::string settingName);
  bool isNumber(std::string settingName);
  bool isAggregate(std::string settingName);

  int searchString(std::string settingName, std::string &out);
  int searchInt(std::string settingName, int &out);
  int searchFloat(std::string settingName, float &out);
  int searchBool(std::string settingName, bool &out);

  int rewriteString(std::string settingName, const std::string &value);
  int rewriteInt(std::string settingName, int value);
  int rewriteFloat(std::string settingName, float value);
  int rewriteBool(std::string settingName, bool value);

  int addString(std::string settingName, std::string value);
  int addInt(std::string settingName, int value);
  int addFloat(std::string settingName, float value);
  int addBool(std::string settingName, bool value);

  std::string getConfigFilename() const;
  void setConfigFilename(const std::string &newConfigName);
};

#endif // CONFIGPROCESSOR_H
