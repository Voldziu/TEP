cmake_minimum_required(VERSION 3.26)
project(Lista3)

set(CMAKE_CXX_STANDARD 98)

add_executable(Lista3 main.cpp
        CTree.cpp
        CTree.h
        constants.h
        UI.tpp
        UI.h
        functionalities.cpp
        functionalities.h
        CTree.tpp
        UI.cpp)
