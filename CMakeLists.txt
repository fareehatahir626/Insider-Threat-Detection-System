cmake_minimum_required(VERSION 3.10)
project(InsiderThreatDetectionSystem)

# Set the C++ standard to C++14 as per the original Makefile
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directory
include_directories(ITDS/include)

# Find all source files
file(GLOB SOURCES "ITDS/src/*.cpp")

# Exclude test_main.cpp from the main executable if it exists
list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ITDS/src/test_main.cpp")

# Create the main executable
add_executable(InsiderThreatDetectionSystem ${SOURCES})

# If a test_main.cpp exists in the tests folder, create a test executable
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_main.cpp")
    # Need to include the classes but exclude main.cpp
    file(GLOB TEST_SOURCES "ITDS/src/*.cpp")
    list(REMOVE_ITEM TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/ITDS/src/main.cpp")
    
    add_executable(RunTests tests/test_main.cpp ${TEST_SOURCES})
    enable_testing()
    add_test(NAME AllTests COMMAND RunTests)
endif()
