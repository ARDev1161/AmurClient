var searchData=
[
  ['changehandspwm_6',['changeHandsPWM',['../classPeripheralController.html#af5dac1876a799cb918e1482271a8635a',1,'PeripheralController']]],
  ['changewheelspwm_7',['changeWheelsPWM',['../classPeripheralController.html#a2b09e9718c6c6b2641eb8fd0c1e05872',1,'PeripheralController']]],
  ['channel_8',['CHANNEL',['../classSPI.html#ae7640e594dd938755624fc1c893681f9',1,'SPI::CHANNEL()'],['../classI2C.html#a445a5d9043fdd31053f672913a617271',1,'I2C::CHANNEL()']]],
  ['checkconn_9',['checkConn',['../classgrpcServer.html#a7d29d1294fbe427f27a44e9fd3a671bb',1,'grpcServer']]],
  ['checkmotorstime_10',['checkMotorsTime',['../classPeripheralController.html#a2201ca5e4db0cc5c9f1752fa53e84ae9',1,'PeripheralController']]],
  ['client_20software_20for_20amur_20distribution_20board_20_28adb_2d0_2e42_29_11',['Client software for Amur distribution board (ADB-0.42)',['../md_README.html',1,'']]],
  ['client_2ecpp_12',['client.cpp',['../client_8cpp.html',1,'']]],
  ['client_2eh_13',['client.h',['../client_8h.html',1,'']]],
  ['clientchannel_14',['clientChannel',['../classgrpcClient.html#ac52219f3b5cc9b95c359cd4aaf03ab90',1,'grpcClient']]],
  ['clientstatus_15',['clientStatus',['../classNetworkController.html#a359fa99529c7cae60f37c9fab7c66080',1,'NetworkController']]],
  ['clkinhibitepin_16',['clkInhibitePin',['../structRegisterSettings_1_1HC165Pins.html#a551fa89adfc72a90dcb37d97cfda339e',1,'RegisterSettings::HC165Pins']]],
  ['clkpin_17',['clkPin',['../structRegisterSettings_1_1HC165Pins.html#ae8d615c74ab2be74d287aa851e0c1ab2',1,'RegisterSettings::HC165Pins::clkPin()'],['../structRegisterSettings_1_1HC595Pins.html#a581c18b71f2c633676ade53f13ebda63',1,'RegisterSettings::HC595Pins::clkPin()']]],
  ['cmake_5fminimum_5frequired_18',['cmake_minimum_required',['../CMakeLists_8txt.html#accaebcd31c7e3e3d3eaaffa8c006e293',1,'cmake_minimum_required(VERSION 3.13 FATAL_ERROR) project(AmurClient VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 14) set(CMAKE_CXX_STANDARD_REQUIRED True) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) if(NOT IS_SUBPROJECT) find_package(Doxygen) message(STATUS &quot;Doxygen $:&#160;CMakeLists.txt'],['../modules_2CMakeLists_8txt.html#aca820f58f342b632aadd9e0f87085563',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(PeripheralController VERSION 0.88 LANGUAGES CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) find_path(pigpio_INCLUDE_DIR NAMES pigpio.h pigpiod_if.h pigpiod_if2.h HINTS/usr/local/include) find_library(pigpio_LIBRARY NAMES libpigpio.so HINTS/usr/local/lib) find_library(pigpiod_if_LIBRARY NAMES libpigpiod_if.so HINTS/usr/local/lib) find_library(pigpiod_if2_LIBRARY NAMES libpigpiod_if2.so HINTS/usr/local/lib) set(pigpio_INCLUDE_DIRS $:&#160;CMakeLists.txt'],['../modules_2interfaces_2CMakeLists_8txt.html#accac77f366b7af950a72e82064dfe8a7',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(InterfacesController VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) include_directories(spi) include_directories(i2c) include_directories(uart) set(SPI spi/spi.cpp spi/spi.h) set(I2C i2c/i2c.cpp i2c/i2c.h) set(UART uart/uart.cpp uart/uart.h) set(INTERFACES $:&#160;CMakeLists.txt'],['../modules_2pwm_2CMakeLists_8txt.html#ae577f980e5fe87271a09d2ce1a305b8f',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(PWMController VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) set(PWM_CONTROLLER pwmcontroller.cpp pwmcontroller.h pwmsettings.h) add_library(PWMController STATIC $:&#160;CMakeLists.txt'],['../modules_2registers_2CMakeLists_8txt.html#ac236152e56b736a28f6cc51106cc8868',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(RegisterController VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) include_directories(hc165) include_directories(hc595) set(HC165 hc165/hc165.cpp hc165/hc165.h) set(HC595 hc595/hc595.cpp hc595/hc595.h) set(REG_CONTROLLER registercontroller.cpp registercontroller.h registerssettings.h) set(REGISTERS $:&#160;CMakeLists.txt'],['../network_2CMakeLists_8txt.html#a73928c85b944d4a9a1be958557cdd802',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(NetworkController VERSION 0.88 LANGUAGES CXX) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) add_subdirectory(protobuf) set(CLIENT_LIB client.cpp client.h) set(SERVER_LIB server.cpp server.h) set(NETWORK_LIB networkcontroller.cpp networkcontroller.h $:&#160;CMakeLists.txt'],['../timer_2CMakeLists_8txt.html#a3ed320434389b18be2f56b2c90020987',1,'cmake_minimum_required(VERSION 3.8 FATAL_ERROR) project(TimerCallback VERSION 0.88 LANGUAGES C CXX) set(CMAKE_CXX_STANDARD 11) set(CMAKE_CXX_STANDARD_REQUIRED ON) get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY) set(TIMER Timer.cpp Timer.h TimerCallback.h) find_library(LIBRT rt) add_library(TimerCallback SHARED $:&#160;CMakeLists.txt']]],
  ['cmakelists_2etxt_19',['CMakeLists.txt',['../CMakeLists_8txt.html',1,'(Global Namespace)'],['../modules_2CMakeLists_8txt.html',1,'(Global Namespace)'],['../modules_2interfaces_2CMakeLists_8txt.html',1,'(Global Namespace)'],['../modules_2pwm_2CMakeLists_8txt.html',1,'(Global Namespace)'],['../modules_2registers_2CMakeLists_8txt.html',1,'(Global Namespace)'],['../network_2CMakeLists_8txt.html',1,'(Global Namespace)'],['../timer_2CMakeLists_8txt.html',1,'(Global Namespace)']]],
  ['config_20',['config',['../classConfigProcessor.html#ab86df02087086358651384907683a70b',1,'ConfigProcessor::config()'],['../classLogicController.html#a4be7553f654f707cd45e4ce29d025c18',1,'LogicController::config()']]],
  ['configname_21',['configName',['../classConfigProcessor.html#a3892fba09b183683d84f7d3e0f2fff64',1,'ConfigProcessor::configName()'],['../classLogicController.html#a0786e8e12fc5511ff29ed2b033761107',1,'LogicController::configName()']]],
  ['configprocessor_22',['ConfigProcessor',['../classConfigProcessor.html',1,'ConfigProcessor'],['../classConfigProcessor.html#a5168059dfc8094a8b91d96ee88e95ace',1,'ConfigProcessor::ConfigProcessor()'],['../classConfigProcessor.html#a09fe56d6b694cf537a8479f44e615a9b',1,'ConfigProcessor::ConfigProcessor(const char *configName)']]],
  ['configprocessor_2ecpp_23',['configprocessor.cpp',['../configprocessor_8cpp.html',1,'']]],
  ['configprocessor_2eh_24',['configprocessor.h',['../configprocessor_8h.html',1,'']]],
  ['configsearchdouble_25',['configSearchDouble',['../classConfigProcessor.html#ab961c866035766abb7682c308ce9271c',1,'ConfigProcessor']]],
  ['configsearchint_26',['configSearchInt',['../classConfigProcessor.html#a6137b024b7216bf64ad6707e82caca76',1,'ConfigProcessor']]],
  ['configsearchstring_27',['configSearchString',['../classConfigProcessor.html#a4348c04f108a9906e2508ad28470b498',1,'ConfigProcessor']]],
  ['connecttoserver_28',['connectToServer',['../classLogicController.html#ad02314f4890c68a236516131e598718d',1,'LogicController::connectToServer()'],['../classLogicController.html#a351da730659ddfcea0a7eeb23c37eddb',1,'LogicController::connectToServer(std::string host, unsigned int port)']]],
  ['controls_29',['controls',['../classLogicController.html#a2d8c84e7b447ede69ac20a06674f0606',1,'LogicController::controls()'],['../classgrpcClient.html#a1ac5714797747ea22e0219564720196a',1,'grpcClient::controls()'],['../classNetworkController.html#a4f6c59f3f555f0b6db17d51a42d221f9',1,'NetworkController::controls()'],['../classgrpcServer.html#abb919e27332b808d51f03a8585b34791',1,'grpcServer::controls()']]],
  ['controlsperi_30',['controlsPeri',['../classPeripheralController.html#af83d3fd9f5d536079e89ce6967600973',1,'PeripheralController']]],
  ['controlsprev_31',['controlsPrev',['../classLogicController.html#a81c650d4d95e2ce6366fc68ec4dab069',1,'LogicController']]],
  ['cpptimereventrunnable_32',['cppTimerEventRunnable',['../classTimerCallback.html#a8d72579d52b4ee4fb7de679111526c84',1,'TimerCallback']]]
];