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

# Examples
# =============================================================================
if(TWEEDLEDEE_EXAMPLES)
  add_subdirectory(examples EXCLUDE_FROM_ALL)
endif()
