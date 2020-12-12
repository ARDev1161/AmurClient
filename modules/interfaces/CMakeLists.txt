cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(InterfacesController VERSION 0.88 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

include_directories(spi)
include_directories(i2c)
include_directories(uart)

set(SPI
    spi/spi.cpp
    spi/spi.h
)

set(I2C
    i2c/i2c.cpp
    i2c/i2c.h
)

set(UART
    uart/uart.cpp
    uart/uart.h
)

set(INTERFACES
    ${SPI}
    ${I2C}
    ${UART}
    )

add_library(InterfacesController 
            STATIC 
            ${INTERFACES}
           )

#add_executable(RegisterController main.cpp ${INTERFACES})
