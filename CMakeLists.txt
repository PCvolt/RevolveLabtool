cmake_minimum_required(VERSION 3.19)
project(RevolveLabtool)

set(CMAKE_CXX_STANDARD 20)

add_library(Labtool SHARED src/DLLMain.cpp src/EntryPoint.cpp
                           src/EntryPoint.hpp)

add_executable(RevolveLabtool src/DLLInjector.cpp)
