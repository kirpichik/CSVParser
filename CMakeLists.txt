cmake_minimum_required(VERSION 3.0)

project(CSVParser)

add_definitions(-std=c++14)

include_directories(.)

set(TARGET_SOURCES
  main.cpp
)

file(GLOB TEST_SOURCES
  tests/*.cpp
  gtest/*.cc
)

# Main

add_executable(CSVParser ${TARGET_SOURCES})

# Tests

add_executable(CSVParserTests ${TEST_SOURCES})

target_link_libraries(CSVParserTests pthread)
