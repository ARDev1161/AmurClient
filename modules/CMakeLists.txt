cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(PeripheralController VERSION 0.88 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

################################################################################
### Find the pigpio shared libraries.
################################################################################

# Find the path to the pigpio includes.
find_path(pigpio_INCLUDE_DIR 
	NAMES pigpio.h pigpiod_if.h pigpiod_if2.h
	HINTS /usr/local/include)
	
# Find the pigpio libraries.
find_library(pigpio_LIBRARY 
	NAMES libpigpio.so
	HINTS /usr/local/lib)
find_library(pigpiod_if_LIBRARY 
	NAMES libpigpiod_if.so
	HINTS /usr/local/lib)
find_library(pigpiod_if2_LIBRARY 
	NAMES libpigpiod_if2.so
	HINTS /usr/local/lib)
    
# Set the pigpio variables to plural form to make them accessible for 
# the paramount cmake modules.
set(pigpio_INCLUDE_DIRS ${pigpio_INCLUDE_DIR})
set(pigpio_INCLUDES     ${pigpio_INCLUDE_DIR})

# Handle REQUIRED, QUIET, and version arguments 
# and set the <packagename>_FOUND variable.
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(pigpio 
    DEFAULT_MSG 
    pigpio_INCLUDE_DIR pigpio_LIBRARY pigpiod_if_LIBRARY pigpiod_if2_LIBRARY)

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
