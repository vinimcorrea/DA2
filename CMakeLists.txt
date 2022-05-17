cmake_minimum_required(VERSION 3.20)
project(second_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(second_project main.cpp Classes/Database.cpp Classes/Algorithm.cpp Classes/Algorithm.h)
