cmake_minimum_required(VERSION 3.19)
project(RevolveLabtool)

set(CMAKE_CXX_STANDARD 20)

# RevolveLib.lib
add_library(
  RevolveLib STATIC
  src/revolveLib/RevolveLib.hpp src/revolveLib/Address.hpp
  src/revolveLib/Address.cpp src/revolveLib/Character.cpp
  src/revolveLib/Character.hpp)
target_include_directories(RevolveLib PRIVATE src/revolveLib)

# Labtool.dll
add_library(Labtool SHARED src/injector/DLLMain.cpp src/labtool/EntryPoint.cpp
                           src/labtool/EntryPoint.hpp)
target_include_directories(Labtool PRIVATE src/labtool src/injector)

target_link_libraries(Labtool PRIVATE RevolveLib)

# RevolveLabtool.exe
add_executable(RevolveLabtool src/injector/DLLInjector.cpp)
target_include_directories(RevolveLabtool PRIVATE src/injector)
