cmake_minimum_required(VERSION 3.7)
project(kernelConvolution)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp Filter.cpp Filter.h value_range.h)
add_executable(kernelConvolution ${SOURCE_FILES})