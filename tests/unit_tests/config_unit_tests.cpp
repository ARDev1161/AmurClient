#include "../../config/configprocessor.h"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

namespace fs = std::filesystem;

// Tests for readConfig function
class readConfig : public ::testing::Test {
protected:
  ConfigProcessor *config;
  fs::path filepath;

  void SetUp() {
    filepath = fs::temp_directory_path();
    filepath.append("amur_test_config_read");
    if (fs::exists(filepath))
      fs::remove(filepath);

    config = new ConfigProcessor(filepath);
  }

  void TearDown() {
    fs::remove(filepath);
    filepath.clear();
    delete config;
  }
};

TEST_F(readConfig, emptyFilename) {
  // Test when config filename is empty. Expectation of failure.
  ASSERT_EQ(EXIT_FAILURE, config->readConfig(""));

  config->setConfigFilename("");
  ASSERT_EQ(EXIT_FAILURE, config->readConfig());
}

TEST_F(readConfig, notExist) {
  // Test when config file are not exist. Expectation of failure.
  ASSERT_EQ(EXIT_FAILURE, config->readConfig(filepath));

  config->setConfigFilename(filepath);
  ASSERT_EQ(EXIT_FAILURE, config->readConfig());
}

TEST_F(readConfig, exist) {
  // Test when config file are exist. Expectation of success.
  std::ofstream outfile(filepath);
  outfile << "" << std::endl;

  ASSERT_EQ(EXIT_SUCCESS, config->readConfig(filepath));

  config->setConfigFilename(filepath);
  ASSERT_EQ(EXIT_SUCCESS, config->readConfig());
}

TEST_F(readConfig, wrongFormat) {
  // Test when config file have wrong content. Expectation of success.
  std::ofstream outfile(filepath);
  outfile << "test \"string\" " << std::endl;

  ASSERT_EQ(EXIT_FAILURE, config->readConfig(filepath));

  config->setConfigFilename(filepath);
  ASSERT_EQ(EXIT_FAILURE, config->readConfig());
}

// Tests for writeConfig function
class writeConfig : public ::testing::Test {
protected:
  ConfigProcessor *config;
  fs::path filepath;

  void SetUp() {}

  void TearDown() {
    filepath.clear();
    delete config;
  }
};

TEST_F(writeConfig, wrongPath) {
  // Restricted symbols in path
  config = new ConfigProcessor("amur_test_config_write_!@#$%^&*()|/.,");
  ASSERT_EQ(EXIT_FAILURE, config->writeConfig());
}

TEST_F(writeConfig, emptyPath) {
  // Empty path
  config = new ConfigProcessor("");
  ASSERT_EQ(EXIT_FAILURE, config->writeConfig());
}

TEST_F(writeConfig, existedFile) {
  // Test write config when file does exist. Expectation of success.
  filepath = fs::temp_directory_path();
  filepath.append("amur_test_config_write");
  if (fs::exists(filepath))
    fs::remove(filepath);

  std::ofstream outfile(filepath);
  outfile << "test = \"string\"; " << std::endl;

  config = new ConfigProcessor(filepath);

  config->rewriteString("test", "new-value");
  ASSERT_EQ(EXIT_SUCCESS, config->writeConfig());
  fs::remove(filepath);
}

TEST_F(writeConfig, removedFile) {
  // Test write config when file does not exist. Expectation of success.
  filepath = fs::temp_directory_path();
  filepath.append("amur_test_config_write");
  if (fs::exists(filepath))
    fs::remove(filepath);

  config = new ConfigProcessor(filepath);

  ASSERT_EQ(EXIT_SUCCESS, config->writeConfig());
  fs::remove(filepath);
}

// Tests for isScalar, isNumber & isAggregate functions
class isType : public ::testing::Test {
protected:
  ConfigProcessor *config;
  fs::path filepath;

  void SetUp() {
    filepath = fs::temp_directory_path();
    filepath.append("amur_test_config_istype");
    if (fs::exists(filepath))
      fs::remove(filepath);

    std::ofstream outfile(filepath);
    outfile << "aggregate:" << std::endl
            << "{" << std::endl
            << "scalar = \"int float bool string \"; " << std::endl
            << "number = 42;" << std::endl
            << "};" << std::endl;

    config = new ConfigProcessor(filepath);
  }

  void TearDown() {
    fs::remove(filepath);
    filepath.clear();
    delete config;
  }
};

TEST_F(isType, emptySettingName) {
  // Test with empty setting name
  ASSERT_EQ(libconfig::Setting::TypeNone, config->isNumber(""));
  ASSERT_EQ(libconfig::Setting::TypeNone, config->isScalar(""));
  ASSERT_EQ(libconfig::Setting::TypeNone, config->isAggregate(""));
}

TEST_F(isType, noSetting) {
  // Test for non existed setting
  ASSERT_EQ(libconfig::Setting::TypeNone, config->isNumber("nonexist"));
  ASSERT_EQ(libconfig::Setting::TypeNone, config->isScalar("nonexist"));
  ASSERT_EQ(libconfig::Setting::TypeNone, config->isAggregate("nonexist"));
}

TEST_F(isType, checkScalar) {
  ASSERT_EQ(true, config->isScalar("aggregate.scalar")); // Test if scalar
}

TEST_F(isType, checkNonScalar) {
  ASSERT_EQ(false, config->isScalar("aggregate")); // Test if not scalar
}

TEST_F(isType, checkNumber) {
  ASSERT_EQ(true, config->isNumber("aggregate.number")); // Test if number
}

TEST_F(isType, checkNonNumber) {
  ASSERT_EQ(false, config->isNumber("aggregate")); // Test if not number
}

TEST_F(isType, checkAggregate) {
  ASSERT_EQ(true, config->isAggregate("aggregate")); // Test if aggregate
}

TEST_F(isType, checkNonAggregate) {
  ASSERT_EQ(false,
            config->isAggregate("aggregate.number")); // Test if not aggregate
}

// Tests for getType function
class getType : public ::testing::Test {
protected:
  ConfigProcessor *config;
  fs::path filepath;

  void SetUp() {
    filepath = fs::temp_directory_path();
    filepath.append("amur_test_config_gettype");
    if (fs::exists(filepath))
      fs::remove(filepath);

    std::ofstream outfile(filepath);
    outfile << "group:" << std::endl
            << "{" << std::endl
            << "bool = true;" << std::endl
            << "float = 0.42;" << std::endl
            << "int = 42;" << std::endl
            << "int64 = 42L;" << std::endl
            << "string = \"usual string \"; " << std::endl
            << "};" << std::endl
            << "array = [ ]; " << std::endl
            << "list = ( ); " << std::endl;

    config = new ConfigProcessor(filepath);
  }

  void TearDown() {
    fs::remove(filepath);
    filepath.clear();
    delete config;
  }
};

TEST_F(getType, emptySettingName) {
  ASSERT_EQ(libconfig::Setting::TypeNone, config->getType(""));
}

TEST_F(getType, checkBool) {
  ASSERT_EQ(libconfig::Setting::TypeBoolean, config->getType("group.bool"));
}

TEST_F(getType, checkFloat) {
  ASSERT_EQ(libconfig::Setting::TypeFloat, config->getType("group.float"));
}

TEST_F(getType, checkInt) {
  ASSERT_EQ(libconfig::Setting::TypeInt, config->getType("group.int"));
}

TEST_F(getType, checkInt64) {
  ASSERT_EQ(libconfig::Setting::TypeInt64, config->getType("group.int64"));
}

TEST_F(getType, checkString) {
  ASSERT_EQ(libconfig::Setting::TypeString, config->getType("group.string"));
}

TEST_F(getType, checkGroup) {
  ASSERT_EQ(libconfig::Setting::TypeGroup, config->getType("group"));
}

TEST_F(getType, checkArray) {
  ASSERT_EQ(libconfig::Setting::TypeArray, config->getType("array"));
}

TEST_F(getType, checkList) {
  ASSERT_EQ(libconfig::Setting::TypeList, config->getType("list"));
}

// Tests for search functions
class searchSetting : public ::testing::Test {
protected:
  ConfigProcessor *config;
  fs::path filepath;

  std::string outString;
  int outInt;
  float outFloat;
  bool outBool;

  void SetUp() {
    filepath = fs::temp_directory_path();
    filepath.append("amur_test_config_gettype");
    if (fs::exists(filepath))
      fs::remove(filepath);

    std::ofstream outfile(filepath);
    outfile << "group:" << std::endl
            << "{" << std::endl
            << "bool = true;" << std::endl
            << "float = 0.42;" << std::endl
            << "int = 42;" << std::endl
            << "int64 = 42L;" << std::endl
            << "string = \"usual string\"; " << std::endl
            << "};" << std::endl
            << "array = [ ]; " << std::endl
            << "list = ( ); " << std::endl;

    config = new ConfigProcessor(filepath);
  }

  void TearDown() {
    outBool = false;
    outFloat = 0.0;
    outString = "";
    outInt = 0;

    fs::remove(filepath);
    filepath.clear();
    delete config;
  }
};

TEST_F(searchSetting, emptySettingName) {
  ASSERT_EQ(EXIT_FAILURE, config->searchString("", outString));
  ASSERT_EQ(EXIT_FAILURE, config->searchInt("", outInt));
  ASSERT_EQ(EXIT_FAILURE, config->searchFloat("", outFloat));
  ASSERT_EQ(EXIT_FAILURE, config->searchBool("", outBool));
}

TEST_F(searchSetting, nonexistedName) {
  ASSERT_EQ(EXIT_FAILURE, config->searchString("nonexist", outString));
  ASSERT_EQ(EXIT_FAILURE, config->searchInt("nonexist", outInt));
  ASSERT_EQ(EXIT_FAILURE, config->searchFloat("nonexist", outFloat));
  ASSERT_EQ(EXIT_FAILURE, config->searchBool("nonexist", outBool));
}

TEST_F(searchSetting, searchString) {
  ASSERT_EQ(EXIT_SUCCESS, config->searchString("group.string", outString));
  ASSERT_EQ("usual string", outString);
}

TEST_F(searchSetting, searchInt) {
  ASSERT_EQ(EXIT_SUCCESS, config->searchInt("group.int", outInt));
  ASSERT_EQ(42, outInt);
}

TEST_F(searchSetting, searchFloat) {
  float res = 0.42;
  ASSERT_EQ(EXIT_SUCCESS, config->searchFloat("group.float", outFloat));
  ASSERT_EQ(res, outFloat);
}

TEST_F(searchSetting, searchBool) {
  ASSERT_EQ(EXIT_SUCCESS, config->searchBool("group.bool", outBool));
  ASSERT_EQ(true, outBool);
}

// Tests for rewrite functions
class rewriteSetting : public ::testing::Test {
protected:
  ConfigProcessor *config;
  fs::path filepath;

  std::string valueString = "string";
  int valueInt = 42;
  float valueFloat = 0.42;
  bool valueBool = true;

  void SetUp() {
    filepath = fs::temp_directory_path();
    filepath.append("amur_test_config_gettype");
    if (fs::exists(filepath))
      fs::remove(filepath);

    std::ofstream outfile(filepath);
    outfile << "group:" << std::endl
            << "{" << std::endl
            << "bool = true;" << std::endl
            << "float = 0.42;" << std::endl
            << "int = 42;" << std::endl
            << "int64 = 42L;" << std::endl
            << "string = \"usual string\"; " << std::endl
            << "};" << std::endl
            << "array = [ ]; " << std::endl
            << "list = ( ); " << std::endl;

    config = new ConfigProcessor(filepath);
  }

  void TearDown() {
    fs::remove(filepath);
    filepath.clear();
    delete config;
  }
};

TEST_F(rewriteSetting, emptySettingName) {
  ASSERT_EQ(EXIT_FAILURE, config->rewriteString("", valueString));
  ASSERT_EQ(EXIT_FAILURE, config->searchInt("", valueInt));
  ASSERT_EQ(EXIT_FAILURE, config->searchFloat("", valueFloat));
  ASSERT_EQ(EXIT_FAILURE, config->searchBool("", valueBool));
}

TEST_F(rewriteSetting, notExisted) {
  ASSERT_EQ(EXIT_FAILURE, config->rewriteString("nonexist", valueString));
  ASSERT_EQ(EXIT_FAILURE, config->searchInt("nonexist", valueInt));
  ASSERT_EQ(EXIT_FAILURE, config->searchFloat("nonexist", valueFloat));
  ASSERT_EQ(EXIT_FAILURE, config->searchBool("nonexist", valueBool));
}

TEST_F(rewriteSetting, nonString) {
  ASSERT_EQ(EXIT_FAILURE, config->rewriteString("group", valueString));
}

TEST_F(rewriteSetting, String) {
  std::string tmp;
  ASSERT_EQ(EXIT_SUCCESS, config->rewriteString("group.string", valueString));
  config->searchString("group.string", tmp);
  ASSERT_EQ(valueString, tmp);
}

TEST_F(rewriteSetting, nonInteger) {
  ASSERT_EQ(EXIT_FAILURE, config->rewriteString("group", valueString));
}

TEST_F(rewriteSetting, Integer) {
  int tmp;
  ASSERT_EQ(EXIT_SUCCESS, config->rewriteInt("group.int", valueInt));
  config->searchInt("group.int", tmp);
  ASSERT_EQ(valueInt, tmp);
}

TEST_F(rewriteSetting, nonFloat) {
  ASSERT_EQ(EXIT_FAILURE, config->rewriteString("group", valueString));
}

TEST_F(rewriteSetting, Float) {
  float tmp;
  ASSERT_EQ(EXIT_SUCCESS, config->rewriteFloat("group.float", valueFloat));
  config->searchFloat("group.float", tmp);
  ASSERT_EQ(valueFloat, tmp);
}

TEST_F(rewriteSetting, nonBool) {
  ASSERT_EQ(EXIT_FAILURE, config->rewriteString("group", valueString));
}

TEST_F(rewriteSetting, Bool) {
  bool tmp;
  ASSERT_EQ(EXIT_SUCCESS, config->rewriteBool("group.bool", valueBool));
  config->searchBool("group.bool", tmp);
  ASSERT_EQ(valueBool, tmp);
}

// Tests for getConfigName & setConfigName functions
TEST(getConfigName, setAndGet) {
  ConfigProcessor config;
  config.setConfigFilename("test_filename_config");
  ASSERT_EQ("test_filename_config", config.getConfigFilename());
}

// int main(int argc, char **argv)
//{
//     ::testing::InitGoogleTest(&argc, argv);

//    return RUN_ALL_TESTS();
//}
