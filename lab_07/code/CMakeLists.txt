cmake_minimum_required(VERSION 3.26.3)

project(code)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(app main.cpp
               algs.h algs.cpp
               measure.h measure.cpp
)