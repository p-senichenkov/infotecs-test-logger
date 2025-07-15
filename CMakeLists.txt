cmake_minimum_required(VERSION 3.24)

project(LoggerTask CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_COLOR_DIAGNOSTICS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/target")

option(STATIC_LIB "Build static library" OFF)
option(TESTS "Build tests" ON)

if(STATIC_LIB)
  set(LIBRARY_TYPE "STATIC")
else()
  set(LIBRARY_TYPE "SHARED")
endif()

add_subdirectory("logger/src")
add_subdirectory("application/src")

if(TESTS)
  add_subdirectory("logger/tests")
endif()
