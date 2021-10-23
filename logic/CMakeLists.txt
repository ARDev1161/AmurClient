cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(LogicModules VERSION 0.88 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

set(AMUR_PILOT
    pilot.cpp
    pilot.h

    mapping/opoint.h
    mapping/opoint.cpp

    mapping/objectsmap.h
    mapping/objectsmap.cpp

    mapping/vector2.h
    )

add_library(LogicModules
            STATIC
            ${AMUR_PILOT}
           )
