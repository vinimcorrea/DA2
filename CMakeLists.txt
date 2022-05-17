cmake_minimum_required(VERSION 3.20)
project(second_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(second_project main.cpp Classes/Database.cpp Classes/Vehicle.cpp Classes/Vehicle.h Classes/Place.cpp Classes/Place.h Classes/Trip.cpp Classes/Trip.h Classes/Algorithm.cpp Classes/Algorithm.h)
