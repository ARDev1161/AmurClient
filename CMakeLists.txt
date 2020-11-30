cmake_minimum_required(VERSION 3.0)

project(AmurClient VERSION 0.88 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

#option(AMURCLIENT_TESTING "Включить модульное тестирование" ON)
#option(AMURCLIENT_COVERAGE "Включить измерение покрытия кода тестами" OFF)

#enable_testing()

#dadd_compile_options(
#    -Werror

#    -Wall
#    -Wextra
#    -Wpedantic

#    -Wcast-align
#    -Wcast-qual
#    -Wconversion
#    -Wctor-dtor-privacy
#    -Wenum-compare
#    -Wfloat-equal
#    -Wnon-virtual-dtor
#    -Wold-style-cast
#    -Woverloaded-virtual
#    -Wredundant-decls
#    -Wsign-conversion
#    -Wsign-promo
#)

#if(NOT CMAKE_CXX_EXTENSIONS)
#    set(CMAKE_CXX_EXTENSIONS OFF)
#endif()

add_subdirectory(network)
add_subdirectory(modules)
add_subdirectory(timer)

set(LOGIC_CONTROLLER
    logiccontroller.cpp
    logiccontroller.h
   )

add_executable(AmurClient AmurClient.cpp ${LOGIC_CONTROLLER})

target_link_libraries(AmurClient
                      NetworkController
                      TimerCallback
                      PeripheralController
                      )