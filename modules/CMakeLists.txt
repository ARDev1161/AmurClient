cmake_minimum_required(VERSION 3.5)

project(PeripheralController LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

# Добавление подпроекта, указывается имя директории
add_subdirectory(registers)
add_subdirectory(pwm)
add_subdirectory(interfaces)

set(PERI_CONTROLLER
    peripheralcontroller.cpp
    peripheralcontroller.h
    peripheralsettings.h

    ../timer/TimerCallback.h
    )

set(PERIPHERAL
    ${PERI_CONTROLLER}
    )
    
add_library(PeripheralController
            STATIC
            ${PERIPHERAL}
           )

target_link_libraries(PeripheralController
                      RegisterController
                      PWMController
                      InterfacesController
                      )

#add_executable(PeripheralController main.cpp ${PERIPHERAL})
