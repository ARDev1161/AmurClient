cmake_minimum_required(VERSION 3.5)

project(System LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

set(SHELL
    shell.h shell.cpp
)

set(SYSTEM
    system.h system.cpp
    systeminfo.h systeminfo.cpp
)

add_library(${PROJECT_NAME} STATIC
            ${SYSTEM}
            ${SHELL}
           )
