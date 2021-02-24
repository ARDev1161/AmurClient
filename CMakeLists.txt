cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

project(AmurClient VERSION 0.88 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

get_directory_property(IS_SUBPROJECT PARENT_DIRECTORY)

#option(AMURCLIENT_TESTING "Включить модульное тестирование" ON)
#option(AMURCLIENT_COVERAGE "Включить измерение покрытия кода тестами" OFF)

#enable_testing()

if(NOT IS_SUBPROJECT)
    find_package(Doxygen)
    message(STATUS "Doxygen ${DOXYGEN_FOUND} - version ${DOXYGEN_VERSION} ")
    message(STATUS "Doxygen dot ${DOXYGEN_DOT_FOUND}")
    
#    add_subdirectory(doc)
    
    if (Doxygen_FOUND)
        if (NOT MYLIB_DOXYGEN_LANGUAGE)
            set(MYLIB_DOXYGEN_LANGUAGE Russian)
        endif()
        
        message(STATUS "Doxygen documentation will be generated in ${MYLIB_DOXYGEN_LANGUAGE}")
        
        add_custom_target(doc COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)    
    endif ()
endif()

add_compile_options(
#    -Werror

    -Wall
    -Wextra
    -Wpedantic

    -Wcast-align
    -Wcast-qual
#    -Wconversion
    -Wsign-conversion
#    -Wsign-promo
    -Wdisabled-optimization
    -Wctor-dtor-privacy
    -Wformat=2
    -Winit-self
    -Wlogical-op
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wnoexcept
#    -Wshadow
    -Wenum-compare
    -Wfloat-equal
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Woverloaded-virtual
    -Wredundant-decls
    -Wstrict-null-sentinel
    -Wstrict-overflow=5
    -Wswitch-default
    -Wundef
    -Wno-unused
)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()

add_subdirectory(network)
add_subdirectory(modules)
add_subdirectory(timer)

set(LOGIC_CONTROLLER
    logiccontroller.cpp
    logiccontroller.h
   )

add_executable(AmurClient AmurClient.cpp ${LOGIC_CONTROLLER})

target_link_libraries(AmurClient
                      NetworkController
                      TimerCallback
                      PeripheralController
                      )
