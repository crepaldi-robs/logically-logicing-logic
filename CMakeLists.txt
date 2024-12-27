# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.16)

# Project name and language
project(ZOL LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories for headers
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find source files in the `src` directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the main executable
add_executable(ZOL ${SOURCES}
        main.cpp)

# Ensure the linker uses the console subsystem
if(WIN32)
    target_link_options(ZOL PRIVATE -Wl,-subsystem,console)
endif()

# Enable unit testing if a `tests` directory exists
if(EXISTS ${CMAKE_SOURCE_DIR}/tests)
    # Enable testing
    enable_testing()

    # Find Google Test
    find_package(GTest REQUIRED)

    # Include directories for Google Test
    include_directories(${GTEST_INCLUDE_DIRS})

    # Find all test files in the `tests` directory
    file(GLOB_RECURSE TEST_SOURCES "tests/*.cpp")

    # Add the test executable
    add_executable(ZOL_tests ${TEST_SOURCES})

    # Link Google Test libraries to the test executable
    target_link_libraries(ZOL_tests PRIVATE GTest::GTest GTest::Main)

    # Add a test command to run all tests
    add_test(NAME AllTests COMMAND ZOL_tests)
endif()
