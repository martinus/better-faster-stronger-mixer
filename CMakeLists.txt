# This file specifies how the project should be built, using CMake.
# If you are unfamiliar with CMake, don't worry about all the details.
# The sections you might want to edit are marked as such, and 
# the comments should hopefully make most of it clear.
#
# For many purposes, you may not need to change anything about this file.

cmake_minimum_required(VERSION 3.8.2)

# Set project name, version and laguages here. (change as needed)
# Version numbers are available by including "exampleConfig.h" in 
# the source. See exampleConfig.h.in for some more details.
project(CPP_BOILERPLATE VERSION 1.0.0 LANGUAGES CXX)


# Options: Things you can set via commandline options to cmake (e.g. -DENABLE_LTO=[ON|OFF])
option(ENABLE_WARNINGS_SETTINGS "Allow target_set_warnings to add flags and defines.
                                 Set this to OFF if you want to provide your own warning parameters." ON)
option(ENABLE_LTO "Enable link time optimization" ON)
option(ENABLE_DOCTESTS "Include tests in the library. Setting this to OFF will remove all doctest related code.
                        Tests in tests/*.cpp will still be enabled." ON)

# Include stuff. No change needed.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
include(ConfigSafeGuards)
include(Colors)
include(CTest)
include(Doctest)
include(Nanobench)
include(Documentation)
#include(LTO)
include(Misc)
include(Warnings)

# Check for LTO support.
#find_lto(CXX)

# --------------------------------------------------------------------------------
#                            Build! (Change as needed)
# --------------------------------------------------------------------------------

set(APP_NAME mixer)

# Add an executable for the file app/main.cpp.
# If you add more executables, copy these lines accordingly.
add_executable(${APP_NAME}
    src/app/doctest.cpp
    src/app/nanobench.cpp

    src/unit/test_bitreverse.cpp

    src/benchmark.cpp
    src/practrand_feeder.cpp
)

# Lib needs its header files, and users of the library must also see these (PUBLIC). (No change needed)
target_include_directories(${APP_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${APP_NAME} PRIVATE doctest)
target_link_libraries(${APP_NAME} PRIVATE nanobench)

target_set_warnings(${APP_NAME} ENABLE ALL AS_ERROR ALL DISABLE Annoying) # Set warnings (if needed).
#target_enable_lto(${APP_NAME} optimized)  # enable link-time-optimization if available for non-debug configurations

# Set the properties you require, e.g. what C++ standard to use. Here applied to library and main (change as needed).
set_target_properties(
    ${APP_NAME}
      PROPERTIES 
        CXX_STANDARD 17 
        CXX_STANDARD_REQUIRED YES 
        CXX_EXTENSIONS NO
)
