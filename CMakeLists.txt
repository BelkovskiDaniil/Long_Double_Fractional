cmake_minimum_required(VERSION 3.23)
project(Long_Double)

set(CMAKE_CXX_STANDARD 14)

add_executable(Long_Double main.cpp big_integer.h operations_integer.cpp utilites.cpp utilites.h big_double.h operations_double.cpp)
