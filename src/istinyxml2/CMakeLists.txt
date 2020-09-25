cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
cmake_policy(VERSION 2.6)
if(POLICY CMP0063)
	cmake_policy(SET CMP0063 OLD)
endif()

project(tinyxml2)

#CMAKE_BUILD_TOOL

################################
# Add definitions

################################
# Add targets
# By Default shared library is being built
# To build static libs also - Do cmake . -DBUILD_STATIC_LIBS:BOOL=ON
# User can choose not to build shared library by using cmake -DBUILD_SHARED_LIBS:BOOL=OFF
# To build only static libs use cmake . -DBUILD_SHARED_LIBS:BOOL=OFF -DBUILD_STATIC_LIBS:BOOL=ON
# To build the tests, use cmake . -DBUILD_TESTS:BOOL=ON
# To disable the building of the tests, use cmake . -DBUILD_TESTS:BOOL=OFF

option(BUILD_SHARED_LIBS "build as shared library" OFF)

# To allow using tinyxml in another shared library
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)

# to distinguish between debug and release lib
set(CMAKE_DEBUG_POSTFIX "d")

add_library(tinyxml2 STATIC tinyxml2.cpp tinyxml2.h)

set_target_properties(tinyxml2 PROPERTIES
        COMPILE_DEFINITIONS "TINYXML2_EXPORT")


if(DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
    target_include_directories(tinyxml2 PUBLIC 
                          $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
                          $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

    if(MSVC)
      target_compile_definitions(tinyxml2 PUBLIC -D_CRT_SECURE_NO_WARNINGS)
    endif(MSVC)
else()
    include_directories(${PROJECT_SOURCE_DIR})

    if(MSVC)
      add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    endif(MSVC)
endif()

# export targets for find_package config mode
export(TARGETS tinyxml2
      FILE ${CMAKE_BINARY_DIR}/${CMAKE_PROJECT_NAME}Targets.cmake)

install(FILES
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME})

install(EXPORT ${CMAKE_PROJECT_NAME}Targets NAMESPACE tinyxml2::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${CMAKE_PROJECT_NAME})
