#ifndef CONFIGPROCESSOR_H
#define CONFIGPROCESSOR_H

#include <libconfig.h++>
#include <iostream>
#include <thread>
#include <mutex>

#if ((LIBCONFIGXX_VER_MAJOR == 1) && (LIBCONFIGXX_VER_MINOR >= 4))
    // использовать возможности, представленные в libconfig 1.4 и новее
#endif


class ConfigProcessor
{
    // libconfig settings
    const char *configName;
    libconfig::Config config;

    libconfig::Setting& root = config.getRoot();
public:
    ConfigProcessor(const char *configName);
    ConfigProcessor();

    int setOptionsConfig ();
    int readConfig (const char *configName);
    int writeConfig(const char *configName);

    std::string configSearchString(const char *settingName);
    int configSearchInt(const char *settingName);
    double configSearchDouble(const char *settingName);

    void getRoot();
    const char *getConfigFilename() const;
    void setConfigFilename(const char *newConfigName);
};

#endif // CONFIGPROCESSOR_H
