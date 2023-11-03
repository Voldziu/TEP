cmake_minimum_required(VERSION 3.26)
add_compile_options(-fno-elide-constructors)

project(Lista2)

set(CMAKE_CXX_STANDARD 98)

add_executable(Lista2 main.cpp
        functionalities.cpp
        functionalities.h
        constants.cpp
        constants.h
        CNumber.cpp
        CNumber.h)
