cmake_minimum_required(VERSION 3.20)
project(second_project)

set(CMAKE_CXX_STANDARD 14)

add_executable(second_project main.cpp
        Classes/Algorithm.cpp Classes/Algorithm.h Classes/Graph.h
        Classes/Graph.cpp Classes/StopVehicle.h Classes/StopVehicle.cpp
        Classes/maxHeap.h Classes/minHeap.h
        )
