cmake_minimum_required(VERSION 3.3)
project(word_scramble_2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

set(SOURCE_FILES main.cpp scrambleheader.h)
add_executable(word_scramble_2 ${SOURCE_FILES})
