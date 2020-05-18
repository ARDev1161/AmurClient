cmake_minimum_required(VERSION 3.0)

project(RegisterController VERSION 0.42 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)


set(SOURCES
    registercontroller.cpp.cpp
    hc165/hc165.cpp
    hc595/hc595.cpp
)

include_directories(hc165)
include_directories(hc595)

add_library(RegisterController SOURCES)
