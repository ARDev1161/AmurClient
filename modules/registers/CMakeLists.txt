cmake_minimum_required(VERSION 3.5)

project(RegisterController VERSION 0.88 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

include_directories(hc165)
include_directories(hc595)

set(HC165
    hc165/hc165.cpp
    hc165/hc165.h
)

set(HC595
    hc595/hc595.cpp
    hc595/hc595.h
)

set(REG_CONTROLLER
    registercontroller.cpp
    registercontroller.h

    registerssettings.h
)

set(REGISTERS
    ${HC165}
    ${HC595}
    ${REG_CONTROLLER}
    )

add_library(RegisterController 
            STATIC
            ${REGISTERS}
           )

#add_executable(RegisterController main.cpp ${REGISTERS})
