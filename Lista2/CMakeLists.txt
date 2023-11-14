cmake_minimum_required(VERSION 3.26)
add_compile_options(-fno-elide-constructors)

project(Lista2)





add_executable(Lista2 main.cpp
        functionalities.cpp
        functionalities.h
        constants.cpp
        constants.h
        CNumber.cpp
        CNumber.h)
set_property(TARGET Lista2 PROPERTY CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")