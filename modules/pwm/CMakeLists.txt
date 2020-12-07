cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(PWMController VERSION 0.88 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

set(PWM_CONTROLLER
    pwmcontroller.cpp
    pwmcontroller.h
    pwmsettings.h
)

add_library(PWMController 
            STATIC 
            ${PWM_CONTROLLER}
           )

#add_executable(PWMController main.cpp ${PWM_CONTROLLER})
