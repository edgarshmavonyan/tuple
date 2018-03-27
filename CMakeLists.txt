cmake_minimum_required(VERSION 3.8)
project(tuple)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES main.cpp tuple.h)
add_executable(tuple ${SOURCE_FILES})
target_link_libraries(tuple gtest gtest_main)