cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(PeripheralController VERSION 0.88 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

find_package(pigpio REQUIRED)
    
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
	   
# if(${pigpio})
#    set(pigpio_lib 
#    	${pigpio}
#	)
#endif()

target_link_libraries(PeripheralController
                      RegisterController
                      PWMController
                      InterfacesController
		      ${pigpio}		      
                      )
