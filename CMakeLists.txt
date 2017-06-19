cmake_minimum_required(VERSION 3.7)
project(kernelConvolution)

set(CMAKE_CXX_STANDARD 14)
include_directories("C:/Users/Viator/Documents/libraries/microsoft_gsl")
set(SOURCE_FILES main.cpp Filter.cpp Filter.h value_range.h gauss_blur.cpp gauss_blur.hpp)
add_executable(kernelConvolution ${SOURCE_FILES})