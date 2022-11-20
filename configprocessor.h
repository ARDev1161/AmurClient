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
    int readConfig (std::string configName);
    int writeConfig();

    int searchString(std::string settingName, std::string &out);
    int searchInt(std::string settingName, int &out);
    int searchDouble(std::string settingName, double &out);
    int searchBool(std::string settingName, bool &out);

    int rewriteString(std::string settingName, std::string value);
    int rewriteInt(std::string settingName, int value);
    int rewriteDouble(std::string settingName, double value);
    int rewriteBool(std::string settingName, bool value);

    int addString(std::string settingName, std::string value);
    int addInt(std::string settingName, int value);
    int addDouble(std::string settingName, double value);
    int addBool(std::string settingName, bool value);

    void getRoot();
    std::string getConfigFilename() const;
    void setConfigFilename(std::string newConfigName);
};

#endif // CONFIGPROCESSOR_H
