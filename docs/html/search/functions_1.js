var searchData=
[
  ['changehandspwm_475',['changeHandsPWM',['../classPeripheralController.html#af5dac1876a799cb918e1482271a8635a',1,'PeripheralController']]],
  ['changewheelspwm_476',['changeWheelsPWM',['../classPeripheralController.html#a2b09e9718c6c6b2641eb8fd0c1e05872',1,'PeripheralController']]],
  ['checkconn_477',['checkConn',['../classgrpcServer.html#a7d29d1294fbe427f27a44e9fd3a671bb',1,'grpcServer']]],
  ['checkmotorstime_478',['checkMotorsTime',['../classPeripheralController.html#a2201ca5e4db0cc5c9f1752fa53e84ae9',1,'PeripheralController']]],
  ['checkstatus_479',['CheckStatus',['../classPilot.html#ab3226cf05b4395ad7ae4f42da5f6b350',1,'Pilot']]],
  ['close_480',['close',['../classI2C.html#a471f8ec5df552b48a69d2ce0bf093da1',1,'I2C']]],
  ['cmake_5fminimum_5frequired_481',['cmake_minimum_required',['../timer_2CMakeLists_8txt.html#a3ed320434389b18be2f56b2c90020987',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(TimerCallback VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) set(TIMER Timer.cpp Timer.h TimerCallback.h) find_library(LIBRT rt) add_library(TimerCallback SHARED $:&#160;CMakeLists.txt'],['../network_2CMakeLists_8txt.html#a73928c85b944d4a9a1be958557cdd802',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(NetworkController VERSION 0.88 LANGUAGES CXX) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) add_subdirectory(protobuf) set(CLIENT_LIB client.cpp client.h) set(SERVER_LIB server.cpp server.h) set(NETWORK_LIB networkcontroller.cpp networkcontroller.h $:&#160;CMakeLists.txt'],['../modules_2registers_2CMakeLists_8txt.html#ac236152e56b736a28f6cc51106cc8868',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(RegisterController VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) include_directories(hc165) include_directories(hc595) set(HC165 hc165/hc165.cpp hc165/hc165.h) set(HC595 hc595/hc595.cpp hc595/hc595.h) set(REG_CONTROLLER registercontroller.cpp registercontroller.h registerssettings.h) set(REGISTERS $:&#160;CMakeLists.txt'],['../modules_2pwm_2CMakeLists_8txt.html#ae577f980e5fe87271a09d2ce1a305b8f',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(PWMController VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) set(PWM_CONTROLLER pwmcontroller.cpp pwmcontroller.h pwmsettings.h) add_library(PWMController STATIC $:&#160;CMakeLists.txt'],['../modules_2interfaces_2CMakeLists_8txt.html#accac77f366b7af950a72e82064dfe8a7',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(InterfacesController VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) include_directories(spi) include_directories(i2c) include_directories(uart) set(SPI spi/spi.cpp spi/spi.h) set(I2C i2c/i2c.cpp i2c/i2c.h) set(UART uart/uart.cpp uart/uart.h) set(INTERFACES $:&#160;CMakeLists.txt'],['../modules_2CMakeLists_8txt.html#aca820f58f342b632aadd9e0f87085563',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(PeripheralController VERSION 0.88 LANGUAGES CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) find_path(pigpio_INCLUDE_DIR NAMES pigpio.h pigpiod_if.h pigpiod_if2.h HINTS/usr/local/include) find_library(pigpio_LIBRARY NAMES libpigpio.so HINTS/usr/local/lib) find_library(pigpiod_if_LIBRARY NAMES libpigpiod_if.so HINTS/usr/local/lib) find_library(pigpiod_if2_LIBRARY NAMES libpigpiod_if2.so HINTS/usr/local/lib) set(pigpio_INCLUDE_DIRS $:&#160;CMakeLists.txt'],['../logic_2CMakeLists_8txt.html#aff58adfb5157aee9418c5d923ac2b661',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(LogicModules VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) set(AMUR_PILOT pilot.cpp pilot.h mapping/opoint.h mapping/opoint.cpp mapping/objectsmap.h mapping/objectsmap.cpp mapping/vector2.h) add_library(LogicModules STATIC $:&#160;CMakeLists.txt'],['../CMakeLists_8txt.html#accaebcd31c7e3e3d3eaaffa8c006e293',1,'cmake_minimum_required(VERSION 3.13 FATAL_ERROR) project(AmurClient VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 14) set(CMAKE_CXX_STANDARD_REQUIRED True) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) if(NOT IS_SUBPROJECT) find_package(Doxygen) message(STATUS &quot;Doxygen $:&#160;CMakeLists.txt']]],
  ['configprocessor_482',['ConfigProcessor',['../classConfigProcessor.html#a5168059dfc8094a8b91d96ee88e95ace',1,'ConfigProcessor::ConfigProcessor()'],['../classConfigProcessor.html#a09fe56d6b694cf537a8479f44e615a9b',1,'ConfigProcessor::ConfigProcessor(const char *configName)']]],
  ['configsearchdouble_483',['configSearchDouble',['../classConfigProcessor.html#ab961c866035766abb7682c308ce9271c',1,'ConfigProcessor']]],
  ['configsearchint_484',['configSearchInt',['../classConfigProcessor.html#a6137b024b7216bf64ad6707e82caca76',1,'ConfigProcessor']]],
  ['configsearchstring_485',['configSearchString',['../classConfigProcessor.html#a4348c04f108a9906e2508ad28470b498',1,'ConfigProcessor']]],
  ['connecttoserver_486',['connectToServer',['../classLogicController.html#ad02314f4890c68a236516131e598718d',1,'LogicController::connectToServer()'],['../classLogicController.html#a351da730659ddfcea0a7eeb23c37eddb',1,'LogicController::connectToServer(std::string host, unsigned int port)']]]
];
