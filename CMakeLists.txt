cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake
project(BaseConverter)  # Name of your project

set(CMAKE_CXX_STANDARD 20)  # Set the C++ standard

# Define the paths for source and include directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCL_DIR ${CMAKE_SOURCE_DIR}/incl)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(MAIN_CXX_DIR ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

# Add all source files to the executable
file(GLOB SOURCES "${SRC_DIR}/*.cc")  # Collects all .cc files in src/

# main code
add_executable(baseconverter ${SOURCES} ${MAIN_CXX_DIR}/main.cc)
# Include the header directory
target_include_directories(baseconverter PRIVATE ${INCL_DIR})


# Add all source files to the executable
file(GLOB TESTS_SOURCES "${TESTS_DIR}/*.cc")  # Collects all .cc files in src/

# testing binary
add_executable(baseconverter_test ${TESTS_SOURCES} ${SOURCES})
# Include the header directory
target_include_directories(baseconverter_test PRIVATE ${INCL_DIR})

# enable testing functionality
enable_testing()

# define tests
add_test(
  NAME BaseConverter_test
  COMMAND $<TARGET_FILE:baseconverter_test>
  )
