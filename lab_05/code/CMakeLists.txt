cmake_minimum_required(VERSION 3.26)

project(code)

set(CMAKE_CXX_STANDARD 17)

add_executable(app main.cpp matrix.cpp matrix.h
                               read.cpp read.h
                               conveyor.cpp conveyor.h
                               measure.cpp measure.h)