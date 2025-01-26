cmake_minimum_required(VERSION 3.10)
project(SinesFileSanitizer VERSION 1.0)

# Create a static library from the source file
add_library(SinesFileSanitizer STATIC SinesFileSanitizer.cpp)

# Specify include directories for the library
target_include_directories(SinesFileSanitizer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>)

# Specify the C++ standard
target_compile_features(SinesFileSanitizer PUBLIC cxx_std_17)

# Include GNU standard installation directories
include(GNUInstallDirs)

# Install the header file to /usr/local/include by default
install(FILES SinesFileSanitizer.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install the static library to /usr/local/lib
install(TARGETS SinesFileSanitizer
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})  # This installs the .a file

# Export the library for use by other projects
install(TARGETS SinesFileSanitizer
    EXPORT SinesFileSanitizerTargets)

# Generate and install the CMake config file to /usr/local/lib/cmake/SinesFileSanitizer by default
install(EXPORT SinesFileSanitizerTargets
    FILE SinesFileSanitizerConfig.cmake
    NAMESPACE SinesFileSanitizer::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/SinesFileSanitizer)
