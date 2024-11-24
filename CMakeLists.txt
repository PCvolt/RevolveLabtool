cmake_minimum_required(VERSION 3.19)
project(RevolveLabtool)

set(CMAKE_CXX_STANDARD 20)

add_library(Labtool SHARED src/injector/DLLMain.cpp src/labtool/EntryPoint.cpp
                           src/labtool/EntryPoint.hpp)

add_executable(RevolveLabtool src/injector/DLLInjector.cpp)
