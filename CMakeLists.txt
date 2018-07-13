# Distributed under the MIT License (See accompanying file /LICENSE )
# Author(s): Bruno Schmitt < bruno [at] oschmitt [dot] com >
# CMake build : tweedledee library
cmake_minimum_required(VERSION 3.8)
project(tweedledee LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Options
# =============================================================================
option(TWEEDLEDEE_EXAMPLES "Build examples" OFF)

# Library
# =============================================================================
add_library(tweedledee INTERFACE)
target_link_libraries(tweedledee INTERFACE c++experimental)
target_include_directories(tweedledee
INTERFACE
  ${PROJECT_SOURCE_DIR}/include)

# Examples
# =============================================================================
if(TWEEDLEDEE_EXAMPLES)
  add_subdirectory(examples EXCLUDE_FROM_ALL)
endif()
