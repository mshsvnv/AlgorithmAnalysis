cmake_minimum_required(VERSION 3.26)

project(code)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(app main.cpp
               inc/algorithms.h src/algorithms.cpp
               inc/matrix.h   src/matrix.cpp
               inc/measure.h   src/measure.cpp
)
