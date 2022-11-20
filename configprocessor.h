#ifndef CONFIGPROCESSOR_H
#define CONFIGPROCESSOR_H

#include <libconfig.h++>
#include <iostream>
#include <vector>

#if ((LIBCONFIGXX_VER_MAJOR == 1) && (LIBCONFIGXX_VER_MINOR >= 4))
    // use features, existed in libconfig 1.4 or newer
#endif


class ConfigProcessor
{
    // libconfig settings
    std::string configName; ///< Setuped config filename
    libconfig::Config config; ///< Libconfig instance

    std::vector<std::string> splitPath(std::string path);
//    libconfig::Setting &root = config.getRoot();
public:
    ConfigProcessor(std::string configName);
    ConfigProcessor();

    int setOptionsConfig ();
    int read (std::string configName);
    int write();

    int search(std::string settingName, std::string &out);
    int search(std::string settingName, int &out);
    int search(std::string settingName, double &out);
    int search(std::string settingName, bool &out);

    int rewrite(std::string settingName, std::string value);
    int rewrite(std::string settingName, int value);
    int rewrite(std::string settingName, double value);
    int rewrite(std::string settingName, bool value);

    int add(std::string settingName, std::string value);
    int add(std::string settingName, int value);
    int add(std::string settingName, double value);
    int add(std::string settingName, bool value);

    void getRoot();
    std::string getConfigFilename() const;
    void setConfigFilename(std::string newConfigName);
};

#endif // CONFIGPROCESSOR_H
