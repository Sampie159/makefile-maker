cmake_minimum_required(VERSION 3.10)

project(MMaker VERSION 2.0)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wpedantic")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(src)

install(
  TARGETS mmaker
  RUNTIME DESTINATION bin
)
