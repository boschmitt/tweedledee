# Distributed under the MIT License (See accompanying file /LICENSE )
# Author(s): Bruno Schmitt
# CMake build : tweedledee library
cmake_minimum_required(VERSION 3.8)
project(tweedledee LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

# Options
# =============================================================================
option(TWEEDLEDEE_EXAMPLES "Build examples" OFF)

# Libs
# =============================================================================
add_subdirectory(libs)

# Library
# =============================================================================
add_library(tweedledee INTERFACE)
target_link_libraries(tweedledee INTERFACE fmt rang spdlog)
target_include_directories(tweedledee
INTERFACE
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/libs)

# Examples
# =============================================================================
if(TWEEDLEDEE_EXAMPLES)
  add_subdirectory(examples)
endif()
