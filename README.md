# pybind11_examples

<!-- MarkdownTOC -->

- [Introduction](#introduction)
- [Cloning this repository](#cloning-this-repository)
- [Dependencies](#dependencies)
    - [Eigen](#eigen)
    - [CMake](#cmake)
- [Examples](#examples)
    - [01_py-list_cpp-vector](#01py-listcpp-vector)
    - [02_py-nested-list_cpp-nested-vector](#02py-nested-listcpp-nested-vector)
    - [03_numpy-1D_cpp-vector](#03numpy-1dcpp-vector)
    - [04_numpy-2D_cpp-vector](#04numpy-2dcpp-vector)
    - [05_numpy-2D_cpp-eigen](#05numpy-2dcpp-eigen)
    - [06_class-numpy-eigen](#06class-numpy-eigen)
    - [07_cpp-overload-scalar](#07cpp-overload-scalar)
    - [08_cpp-overload-eigen](#08cpp-overload-eigen)

<!-- /MarkdownTOC -->

# Introduction

The power of [pybind11](https://github.com/pybind/pybind11) is captured by the following citation from the pybind11 readme:

>   pybind11 is a lightweight header-only library that exposes C++ types in Python and vice versa, mainly to create Python bindings of existing C++ code. Its goals and syntax are similar to the excellent Boost.Python library by David Abrahams ...
>
>   The main issue with Boost.Python - and the reason for creating such a similar project — is Boost. Boost is an enormously large and complex suite of utility libraries that works with almost every C++ compiler in existence. ... Now that C++11-compatible compilers are widely available, this heavy machinery has become an excessively large and unnecessary dependency.

This repository contains several examples for the usage of pybind11. Even though the [online documentation](http://pybind11.readthedocs.io) provided by the developers of pybind11 makes the usage of it relatively straightforward, several examples - such as provided here - make pybind11 even easier to use. These example are meant for you to start quicker with pybind11. They are however by no means exhaustive, and do not always provide the optimal choice. Therefore it is highly advisable to **think for yourself**. Furthermore, contributions with similar simple examples (or by further improving existing examples) are highly welcomed.

To give credit where credit is due:

*   The creators of pybind11 have done a great job! It is really easy to use, and very lightweight. Also the [documentation](http://pybind11.readthedocs.io) is already quite complete.

*   The examples made available by [Cliburn Chan and Janice McCarthy, at Duke University](http://people.duke.edu/~ccc14/sta-663-2016/18G_C++_Python_pybind11.html) have been of enormous help. Please also read their [documentation](http://people.duke.edu/~ccc14/sta-663-2016/18G_C++_Python_pybind11.html).

Note that there are also test-cases included in the [pybind11 repository](https://github.com/pybind/pybind11), but these are not very insightful when you are new to pybind11.

# Cloning this repository

The pybind11 module (which is header only!) is included as a submodule of this repository. This requires some attention when cloning this project. There are two options:

*   The simplest option is:

    ```bash
    git clone --recursive https://github.com/tdegeus/pybind11_examples.git
    ```

    This will download the submodule up to the version that is used in this project. To update to the latest commit of the submodule itself:

    ```bash
    git submodule update --remote
    ```

*   One could also directly download the submodule from the source:

    ```bash
    git clone https://github.com/tdegeus/pybind11_examples.git
    cd pybind11_examples
    git submodule init
    git submodule update
    ```

# Dependencies

## Eigen

The [Eigen](http://eigen.tuxfamily.org) library is used in some of the NumPy examples. From these examples is can be observed that through pybind11, Eigen and NumPy are really handshake modules. Almost no code is needed to create the C++/Python interface. Note that most of the simplicity depends on copies being passed, some attention is needed if one wants to pass purely by reference.

Eigen does not need installation because it is also header-only. One just needs to download the files and include the headers at compile time.

*   For macOS with homebrew:

    ```bash
    brew install eigen
    ```

    Then, compile with

    ```bash
    -I /usr/local/Cellar/eigen/3.3.1/include/eigen3
    ```

    (or something similar specialized to your installation). Note that CMake can find Eigen independently (see below).

## CMake

### Basic usage

pybind11 applications can be compiled very easy using CMake. If one adds pybind11 as a sub-folder of the `src` directory, one can use for example the following `CMakeLists.txt` file:

```cmake
cmake_minimum_required(VERSION 2.8.12)
project(example)

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)
```

(whereby the module consists of a single source file `example.cpp`). To compile it, use:

```bash
cmake .
make
```

### Using Eigen

When Eigen is 'installed' it can be easily included by adding the following in `CMakeLists.txt`:

```cmake
find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} )
```

### Using the C++14 standard

The C++14 standard can be used by including the following in `CMakeLists.txt`:

```cmake
set(CMAKE_CXX_STANDARD 14)
```

# Examples

## 01_py-list_cpp-vector

This example features one function `modify` that takes a list (read-only), multiplies all entries by two, and returns it as a list of doubles (see [`example.cpp`](01_py-list_cpp-vector/example.cpp)). From Python this function is contained in a simple module `example` (see [`test.py`](01_py-list_cpp-vector/test.py)).

The purpose of this example is to show how to make a function accept a list, how to convert this to the standard C++ `std::vector`, and how to return a new `std::vector` (or list).

To compile, either employ CMake, whereby the compilation instructions are read from [`CMakeLists.txt`](01_py-list_cpp-vector/CMakeLists.txt) by subsequently:

```bash
cmake .
make
```

Or, compile directly using:

```bash
c++ -O3 -shared -std=gnu++11 -I ./pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

Run the example by:

```bash
python3 test.py
```

>   To run with Python 2, simply replace the two occurrences of "python3" above with "python". To modify the CMake instructions find more [online](http://pybind11.readthedocs.io/en/master/compiling.html?highlight=cmake).

## 02_py-nested-list_cpp-nested-vector

Same as the [previous example](#01py-listcpp-vector), but with a nested list.

To compile and run follow the instructions [above](#01py-listcpp-vector).

## 03_numpy-1D_cpp-vector

One function `modify` that converts the entries from a one-dimensional array to integers, and then multiplies these entries by 10.

The purpose of this example is to show how to make a function accept an 1-D NumPy array, how to convert this to the standard C++ `std::vector`, and how to return an 1-D NumPy array. Note that the interface generated using pybind11 is so flexible that it even accepts list inputs.

To compile and run follow the instructions [above](#01py-listcpp-vector).

## 04_numpy-2D_cpp-vector

One function `length`. This function accepts a 'matrix' in which comprises a list of 2-D position vectors, as rows. The result is again a 'matrix' with for each row the "x" and "y" position, and the length of the 2-D position vector.

To compile and run follow the instructions [above](#01py-listcpp-vector).

## 05_numpy-2D_cpp-eigen

Two functions `det` and `inv` that use the Eigen library. 

The purpose of this example is to show how trivial the interaction between C++/Eigen and Python/NumPy is.

To compile using CMake and to run, follow the instructions [above](#01py-listcpp-vector) (whereby the Eigen headers are included in [`CMakeLists.txt`](05_numpy-2D_cpp-eigen/CMakeLists.txt). To compile directly, additionally the Eigen headers have to be included:

```bash
c++ -O3 -shared -std=gnu++11 -I /path/to/eigen -I ./pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

For example on macOS with homebrew:

```bash
c++ -O3 -shared -std=gnu++11 -I /usr/local/Cellar/eigen/3.3.1/include/eigen3 -I ./pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

## 06_class-numpy-eigen

A custom `CustomVectorXd` class with one function `mul`. This class uses the Eigen library. It also includes a default argument.

Furthermore, this example has a function `trans` (totally unrelated to the custom `CustomVectorXd` class). It's purpose is to show how to return a new `Eigen::VectorXi` (or NumPy-array).

To compile and run follow the instructions [above](#05numpy-2dcpp-eigen).

## 07_cpp-overload-scalar

One overloaded function `mul`. This function acts 'differently' if it is called with `int` arguments or `double` arguments. Notice that the default behavior of pybind11 is quite robust. When calling the function with one `int` and one `double` argument, the module will choose the `double` version of `mul` (and will cast the `int` argument to a `double`).

To compile using CMake and to run, follow the instructions [above](#01py-listcpp-vector). To compile directly, make sure that the C++14 standard is used:

```bash
c++ -O3 -shared -std=gnu++14 ./pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

## 08_cpp-overload-eigen

Similar to the [previous example](#08cpp-overload-eigen), but with Eigen arguments (i.e. NumPy arguments from the Python side).

To compile using CMake and to run, follow the instructions [above](#01py-listcpp-vector). To compile directly, make sure that the C++14 standard is used, and that the Eigen headers are included:

```bash
c++ -O3 -shared -std=gnu++14 -I /path/to/eigen -I ./pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```
