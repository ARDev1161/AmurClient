cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(TimerCallback VERSION 0.88 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

set(TIMER
    Timer.cpp
    Timer.h
    
    TimerCallback.h
)

add_library(TimerCallback 
            SHARED 
            ${TIMER}
           )
