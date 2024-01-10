cmake_minimum_required(VERSION 3.26)
project(PEA_ACO)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")

add_executable(PEA_ACO main.cpp
        TSP.cpp
        TSP.h)
