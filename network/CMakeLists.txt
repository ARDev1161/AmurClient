cmake_minimum_required(VERSION 3.5.1)

project(NetworkController LANGUAGES CXX)

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
   
set(NETWORK_LIB 
    networkcontroller.cpp 
    networkcontroller.h 
    ${CLIENT_LIB} 
    ${SERVER_LIB} 
    ${PROTOS_LIB}
   )

add_library(NetworkController
            STATIC
            ${NETWORK_LIB}
            )

target_link_libraries(NetworkController AMURProtos)

#add_executable(TestNetController main.cpp)
#target_link_libraries(TestNetController NetworkController
    #AMURProtos
    #)
