cmake_minimum_required(VERSION 3.18)

project(mymodule)

set(CMAKE_CXX_STANDARD 14)

find_package(pybind11 REQUIRED CONFIG)
pybind11_add_module(mymodule code_and_wrapper.cpp)
