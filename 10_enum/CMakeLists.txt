cmake_minimum_required(VERSION 2.8.12)
project(example)

set (CMAKE_CXX_STANDARD 14)

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)
