cmake_minimum_required(VERSION 3.15)
project(Factory)

set(CMAKE_CXX_STANDARD 17)

add_executable(Factory main.cpp package.cpp package.hpp storage_types.hpp storage_types.cpp nodes.hpp nodes.cpp helpers.hpp helpers.cpp)