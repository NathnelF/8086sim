cmake_minimum_required(VERSION 3.15...4.0)

project(8086)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(
  main
  main.cpp
  file.cpp
  table.cpp
  decode.cpp
)
