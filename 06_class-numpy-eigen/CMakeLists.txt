cmake_minimum_required(VERSION 2.8.12)
project(example)

find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} )

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)
