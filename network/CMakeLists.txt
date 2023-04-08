cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

project(NetworkController VERSION 0.88 LANGUAGES CXX)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

add_subdirectory(protobuf)

set(CLIENT_LIB 
    client.cpp 
    client.h
   )
   
set(SERVER_LIB 
    server.cpp 
    server.h
   )

set(ARPER
    arper.h
    arper.cpp
)
   
set(NETWORK_LIB 
    networkcontroller.cpp 
    networkcontroller.h 
    ${ARPER}
    ${CLIENT_LIB} 
    ${SERVER_LIB} 
    ${PROTOS_LIB}
   )

add_library(${PROJECT_NAME}
            STATIC
            ${NETWORK_LIB}
            )

target_link_libraries(${PROJECT_NAME}
    AMURProtos
    System
)
