cmake_minimum_required(VERSION 3.15)
project(Statki)

set(CMAKE_CXX_STANDARD 14)

add_executable(Statki main.cpp grid.cpp grid.h header.h controller.cpp viewer.cpp)