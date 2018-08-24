# Distributed under the MIT License (See accompanying file /LICENSE)
# Author(s): Bruno Schmitt

if (NOT TARGET rang)
  add_library(rang INTERFACE)
  target_include_directories(rang INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/rang)
endif()
