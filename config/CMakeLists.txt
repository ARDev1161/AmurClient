cmake_minimum_required(VERSION 3.5)

project(Config LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

find_library(libСonfig_LIB config++ REQUIRED)

# Copy config from source to build
configure_file(
        ../amur.cfg.in
        ../amur.cfg
        )

set(CONFIG
    configprocessor.h configprocessor.cpp
   )

add_library(${PROJECT_NAME} STATIC
    ${CONFIG}
    )

if(libСonfig_LIB)
    target_link_libraries(${PROJECT_NAME} config++)
endif()
