####################################################################################################################
##                                               RoveSoCameraServer                                               ##
##                                              25.00.00 - Build 001                                              ##
##                                             Mars Rover Design Team                                             ##
##                                      Copyright 2024 - All Rights Reserved                                      ##
####################################################################################################################

## Set CMake Minimum Version
cmake_minimum_required(VERSION 3.24.3)

## C++ and CUDA Version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 20)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

## Project Name and Version
project(RoveSoCameraServer VERSION 25.00.00 LANGUAGES CXX CUDA)
set(EXE_NAME "${PROJECT_NAME}")

## CMake Policies
cmake_policy(SET CMP0146 OLD)    # Allows use of "FindCUDA" function
cmake_policy(SET CMP0153 OLD)    # Allows use of "Exec_Program" function

####################################################################################################################
##                                                    Options                                                     ##
####################################################################################################################

## Enable or Disable Code Coverage Mode
option(BUILD_CODE_COVERAGE "Enable Code Coverage Mode" OFF)

## Enable or Disable Verbose Makefile
option(BUILD_VERBOSE_MODE "Enable Verbose Makefile" OFF)

## Enable or Disable Install Mode
option(BUILD_INSTALL_MODE "Enable Install Mode" OFF)

## Enable or Disable Tests Mode
option(BUILD_TESTS_MODE "Enable Tests Mode" OFF)

## Enable or Disable RoveComm Cross-Compile Mode
option(RC_CROSS_COMPILE "Cross-Compile RoveComm for Windows and Linux" OFF)

## Enable or Disable Printing All CMake Variables
option(LIST_ALL_VARS "Print all CMake Variables" OFF)

####################################################################################################################
##                                         Configuration Based on Options                                         ##
####################################################################################################################

message("-- RoveSoCameraServer System Options:")

## Code Coverage Mode
if (BUILD_CODE_COVERAGE)
    message("--   [x]: Code Coverage: Enabled")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g -fprofile-arcs -ftest-coverage --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
else()
    message("--   [ ]: Code Coverage: Disabled")
endif()

## Verbose Makefile
if (BUILD_VERBOSE_MODE)
    message("--   [x]: Verbose Makefile: Enabled")
    set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "Verbose output" FORCE)
else()
    message("--   [ ]: Verbose Makefile: Disabled")
endif()

## Build Installer
if (BUILD_INSTALL_MODE)
    message("--   [x]: Build Installer: Enabled")
    
else()
    message("--   [ ]: Build Installer: Disabled")
endif()

## Build Unit and Integration Tests
if (BUILD_TESTS_MODE)
    message("--   [x]: Build Unit and Integration Tests: Enabled")
    enable_testing()
else()
    message("--   [ ]: Build Unit and Integration Tests: Disabled")
endif()

## RoveComm Cross-Compile
if (RC_CROSS_COMPILE)
    message("--   [x]: RoveComm Cross-Compile: Enabled")
else()
    message("--   [ ]: RoveComm Cross-Compile: Disabled")
    set(BUILD_WIN OFF CACHE BOOL "Disable Windows Cross-Compile Mode for Autonomy Software" FORCE)
endif()

## Print All CMake Variables
if (LIST_ALL_VARS)
    message("--   [x]: Print All CMake Variables: Enabled")
    
else()
    message("--   [ ]: Print All CMake Variables: Disabled")
endif()

####################################################################################################################
##                                                 CPack Setup                                                    ##
####################################################################################################################

## Define CPack Project Info
set(CPACK_PROJECT_NAME ${EXE_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VENDOR "Mars Rover Design Team")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_SOURCE_DIR}/data/CPACK/logo.ico")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_SYSTEM_NAME}")
set(CPACK_GENERATOR "STGZ")

####################################################################################################################
##                                           Dependencies and Libraries                                           ##
####################################################################################################################

# Configure BSThreadPool
add_compile_definitions(BS_THREAD_POOL_ENABLE_PAUSE=1)
add_compile_definitions(BS_THREAD_POOL_ENABLE_PRIORITY=1)
add_compile_definitions(BS_THREAD_POOL_ENABLE_WAIT_DEADLOCK_CHECK=1)

## Find RoveComm
include_directories(external/rovecomm/src)
add_subdirectory(external/rovecomm)
add_compile_definitions(__ROVECOMM_LIBRARY_MODE__=1)

## Find Threads
find_package(Threads REQUIRED)

## Find Quill
find_package(quill REQUIRED)

## Find Google Test
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

## Find Eigen3.
find_package(Eigen3 3.3 REQUIRED NO_MODULE)

## Find OpenCV.
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

## Find CUDA. Must match ZEDSDK version. Add as system package to supress library warnings.
find_package(CUDAToolkit ${ZED_CUDA_VERSION} REQUIRED)
include_directories(SYSTEM ${CUDAToolkit_INCLUDE_DIRS})

## Add special flag if compiling on aarch64.
if (CMAKE_SYSTEM_PROCESSOR MATCHES aarch64)
    add_definitions(-DJETSON_STYLE)
endif()

## Check if all variables should be listed.
if (LIST_ALL_VARS)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()

####################################################################################################################
##                                                Build Executable                                                ##
####################################################################################################################

## Search Project Directories for CPP Files
file(GLOB_RECURSE SRC           CONFIGURE_DEPENDS  "src/*.cpp")
file(GLOB_RECURSE Tools_SRC     CONFIGURE_DEPENDS  "tools/*.cpp")

add_executable(${EXE_NAME} ${SRC} ${Tools_SRC})

## Compile Options
if (MSVC)
    target_compile_options(${EXE_NAME} PRIVATE /W4 /WX)
else()
    target_compile_options(${EXE_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

## Link Libraries
set(ROVESOCAMERASERVER_LIBRARIES  Threads::Threads
                                  Eigen3::Eigen
                                  RoveComm_CPP
                                  quill::quill
                                  ${OpenCV_LIBS}
)
set(FFMPEG_LIB_DIR /usr/local/lib)
set(FFMPEG_LIBS
    ${FFMPEG_LIB_DIR}/libavformat.a
    ${FFMPEG_LIB_DIR}/libavcodec.a
    ${FFMPEG_LIB_DIR}/libavutil.a
    ${FFMPEG_LIB_DIR}/libswscale.a
    ${FFMPEG_LIB_DIR}/libswresample.a
    ${FFMPEG_LIB_DIR}/libavdevice.a
    ${FFMPEG_LIB_DIR}/libavfilter.a
    ${FFMPEG_LIB_DIR}/libpostproc.a
)

set(ADDITIONAL_LIBS -lz -lm -lpthread -lx264 -ldl -lX11 -llzma -ldrm)

target_link_libraries(${EXE_NAME} PRIVATE ${ROVESOCAMERASERVER_LIBRARIES} ${FFMPEG_LIBS} ${ADDITIONAL_LIBS})


####################################################################################################################
##                                             Installation and Tests                                             ##
####################################################################################################################

## Install Mode
if (BUILD_INSTALL_MODE)
    install(TARGETS ${EXE_NAME} RUNTIME_DEPENDENCIES DIRECTORIES ${ROVESOCAMERASERVER_LIBRARIES} RUNTIME DESTINATION bin)
endif()

## Tests Mode
if (BUILD_TESTS_MODE)
    file(GLOB_RECURSE UnitTests_SRC         CONFIGURE_DEPENDS  "tests/Unit/*.cc")
    file(GLOB_RECURSE IntegrationTests_SRC  CONFIGURE_DEPENDS  "tests/Integration/*.cc")
    file(GLOB         Network_SRC           CONFIGURE_DEPENDS  "src/RoveSoCameraServerNetworking.cpp")
    file(GLOB         Logging_SRC           CONFIGURE_DEPENDS  "src/RoveSoCameraServerLogging.cpp")

    list(LENGTH UnitTests_SRC UnitTests_LEN)
    list(LENGTH IntegrationTests_SRC IntegrationTests_LEN)

    if (UnitTests_LEN GREATER 0)
        add_executable(${EXE_NAME}_UnitTests ${UnitTests_SRC} ${Network_SRC} ${Logging_SRC})
        target_link_libraries(${EXE_NAME}_UnitTests GTest::gtest GTest::gtest_main ${ROVESOCAMERASERVER_LIBRARIES})
        add_test(Unit_Tests ${EXE_NAME}_UnitTests)
    else()
        message("No Unit Tests!")
    endif()

    if (IntegrationTests_LEN GREATER 0)
        add_executable(${EXE_NAME}_IntegrationTests ${IntegrationTests_SRC} ${Network_SRC} ${Logging_SRC})
        target_link_libraries(${EXE_NAME}_IntegrationTests GTest::gtest GTest::gtest_main ${ROVESOCAMERASERVER_LIBRARIES})
        add_test(Integration_Tests ${EXE_NAME}_IntegrationTests)
    else()
        message("No Integration Tests!")
    endif()
endif()

####################################################################################################################
##                                           Final Build Configuration                                            ##
####################################################################################################################

message("-- Final RoveSoCamera Server Configuration Summary")
message("--   Executable Name: ${EXE_NAME}")
message("--   Tests Mode: ${BUILD_TESTS_MODE}")
message("--   Install Mode: ${BUILD_INSTALL_MODE}")
message("--   Code Coverage Mode: ${BUILD_CODE_COVERAGE}")
message("--   Verbose Makefile: ${BUILD_VERBOSE_MODE}")
