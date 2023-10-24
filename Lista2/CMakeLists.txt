cmake_minimum_required(VERSION 3.26)
project(Lista2)

set(CMAKE_CXX_STANDARD 98)

add_executable(Lista2 main.cpp
        functionalities.cpp
        functionalities.h
        constants.cpp
        constants.h
        CNumber.cpp
        CNumber.h)
