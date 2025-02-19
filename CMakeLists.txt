cmake_minimum_required(VERSION 3.19)
project(RevolveLabtool)

set(CMAKE_CXX_STANDARD 20)

# RevolveLib.lib
add_library(
  RevolveLib STATIC
  src/revolveLib/RevolveLib.hpp
  src/revolveLib/Action.hpp
  src/revolveLib/Address.hpp
  src/revolveLib/Address.cpp
  src/revolveLib/Camera.hpp
  src/revolveLib/Camera.cpp
  src/revolveLib/Character.cpp
  src/revolveLib/Character.hpp
  src/revolveLib/PauseMenu.cpp
  src/revolveLib/PauseMenu.hpp
  src/revolveLib/CharacterSelectMenu.cpp
  src/revolveLib/CharacterSelectMenu.hpp
  src/revolveLib/PauseMenu.cpp)
target_include_directories(RevolveLib PRIVATE src/revolveLib)

# Labtool.dll
add_library(
  Labtool SHARED
  src/injector/DLLMain.cpp
  src/labtool/EntryPoint.cpp
  src/labtool/EntryPoint.hpp
  src/labtool/FrameStep.cpp
  src/labtool/FrameStep.hpp
  src/labtool/Hooks.cpp
  src/labtool/Hooks.hpp
  src/labtool/ResetState.cpp
  src/labtool/ResetState.hpp)
target_include_directories(Labtool PRIVATE src/labtool src/injector)

target_link_libraries(Labtool PRIVATE RevolveLib)

# RevolveLabtool.exe
add_executable(RevolveLabtool src/injector/DLLInjector.cpp)
target_include_directories(RevolveLabtool PRIVATE src/injector)
