# Contents

<!-- MarkdownTOC -->

- [Introduction](#introduction)
- [Cloning this repository](#cloning-this-repository)
- [Dependencies](#dependencies)
- [Compiling strategies](#compiling-strategies)
    - [DIY](#diy)
    - [CMake](#cmake)
        - [Basic usage](#basic-usage)
        - [Using Eigen](#using-eigen)
        - [Using the C++14 standard](#using-the-c14-standard)
    - [setup.py](#setuppy)
- [Examples](#examples)
    - [01_py-list_cpp-vector](#01_py-list_cpp-vector)
    - [02_py-nested-list_cpp-nested-vector](#02_py-nested-list_cpp-nested-vector)
    - [03_numpy-1D_cpp-vector](#03_numpy-1d_cpp-vector)
    - [04_numpy-2D_cpp-vector](#04_numpy-2d_cpp-vector)
    - [05_numpy-2D_cpp-eigen](#05_numpy-2d_cpp-eigen)
    - [06_class-numpy-eigen](#06_class-numpy-eigen)
    - [07_cpp-overload-scalar](#07_cpp-overload-scalar)
    - [08_cpp-overload-eigen](#08_cpp-overload-eigen)
    - [09_numpy_cpp-custom-matrix](#09_numpy_cpp-custom-matrix)
    - [10_enum](#10_enum)
    - [11_class-parent-child](#11_class-parent-child)

<!-- /MarkdownTOC -->


# Introduction

The power of [pybind11](https://github.com/pybind/pybind11) is captured by the following citation from pybind11's readme:

>   pybind11 is a lightweight header-only library that exposes C++ types in Python and vice versa, mainly to create Python bindings of existing C++ code. Its goals and syntax are similar to the excellent Boost.Python library by David Abrahams ...
>
>   The main issue with Boost.Python - and the reason for creating such a similar project — is Boost. Boost is an enormously large and complex suite of utility libraries that works with almost every C++ compiler in existence. ... Now that C++11-compatible compilers are widely available, this heavy machinery has become an excessively large and unnecessary dependency.

This repository contains several examples for the usage of pybind11. Even though the [online documentation](http://pybind11.readthedocs.io) provided by the developers of pybind11 makes the usage of it relatively straightforward, several examples - such as provided here - make pybind11 even easier to use. These examples are meant for you to start quicker with pybind11. They are, however, by no means exhaustive, and do not always provide the optimal choice. Therefore it is highly advisable to **think for yourself**. Furthermore, **contributions with similar simple examples (or by further improving existing examples) are highly welcome**. Please file a pull request or an issue on [GitHub](https://github.com/tdegeus/pybind11_examples), or [contact me](mailto:tom_AT_geus.me).

To give credit where credit is due:

*   The creators of pybind11 have done a great job! It is really easy to use, and very lightweight. Also the [documentation](http://pybind11.readthedocs.io) is already quite complete.

*   The examples made available by [Cliburn Chan and Janice McCarthy, at Duke University](http://people.duke.edu/~ccc14/sta-663-2016/18G_C++_Python_pybind11.html) have been of enormous help. Please also read their [documentation](http://people.duke.edu/~ccc14/sta-663-2016/18G_C++_Python_pybind11.html).

Note that there are also test cases that double as examples in the [pybind11 repository](https://github.com/pybind/pybind11), but these are not very insightful when you are new to pybind11.

Finally, pybind11 is actively used. So one can look in actively maintained libraries for specific solutions. For example:

*   [cppmat](http://cppmat.geus.me) is a library that provided multidimensional arrays in C++, much like the [Eigen](http://eigen.tuxfamily.org) library does for one- and two-dimensional arrays. It also provides a pybind11 interface, such that creating a Python module that uses cppmat objects as (return) arguments in the back end functions becomes trivial.

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

The [Eigen](http://eigen.tuxfamily.org) library is used in some of the NumPy examples. From these examples it can be observed that through pybind11, Eigen and NumPy are really handshake modules. Almost no code is needed to create the C++/Python interface. Note that most of the simplicity depends on copies being passed, some attention is needed if one wants to pass purely by reference.

Eigen does not need installation because it is also header only. One just needs to download the files and include the headers at compile time.

In general one can download and install Eigen by:

```bash
mkdir /path/to/temp/build
cmake /path/to/eigen/download
make install
```

> For macOS one could simply use
> 
> ```bash
> brew install eigen
> ```

Thereafter compile with 

```bash
clang++ -I/path/to/eigen/instalation ...
```

Note that, when properly configured (which is normally the case), pkg-config can be used to keep track of the paths:

```bash
clang++ `pkg-config --cflags eigen3` ...
```

Or one can use CMake (see below).

# Compiling strategies

## DIY

If you have a simple library you might want to do everything yourself. In this case you compile your C++ source to a shared object which is linked to Python. This boils down to 

```bash
c++ -O3 -shared -std=gnu++11 -I ./pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

## CMake

### Basic usage

pybind11 applications can be compiled very easy using CMake. For simplicity pybind11 is included as a sub-folder of the examples below (in fact using a symbolic link to over many copies), so that we can use a `CMakeLists.txt` like:

```cmake
cmake_minimum_required(VERSION 2.8.12)
project(example)

add_subdirectory(pybind11)
pybind11_add_module(example example.cpp)
```

(whereby this example module consists of a single source file `example.cpp`). To compile it, use:

```bash
cd /path/to/build
cmake /path/to/example/src
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

## setup.py

A file `setup.py` can be added to your library. You can then compile and install using

```bash
python3 setup.py build
python3 setup.py install
```

Although writing the `setup.py` is not hard it is not covered here. One can use some tools included in [cppmat](http://cppmat.geus.me), that can be installed with pip (e.g. `pip3 install cppmat`). Furthermore on can look at the `setup.py` of for example [GooseTensor](https://github.com/tdegeus/GooseTensor) or several other of [my repositories](https://github.com/tdegeus).

# Examples

## [01_py-list_cpp-vector](01_py-list_cpp-vector)

This example features one function `modify` that takes a list (read-only), multiplies all entries by two, and returns it as a list of doubles (see [`example.cpp`](01_py-list_cpp-vector/example.cpp)). From Python this function is contained in a simple module `example` (see [`test.py`](01_py-list_cpp-vector/test.py)).

The purpose of this example is to show how to make a function accept a list, how to convert this to the standard C++ `std::vector`, and how to return a new `std::vector` (or list). Note that the actual operation is not very important, it is the interface that is illustrated.

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

## [02_py-nested-list_cpp-nested-vector](02_py-nested-list_cpp-nested-vector)

Same as the [previous example](#01py-listcpp-vector), but with a nested list.

## [03_numpy-1D_cpp-vector](03_numpy-1D_cpp-vector)

A function `modify` that converts the entries from a one-dimensional array to integers, and then multiplies these entries by 10.

The purpose of this example is to show how to make a function accept a one-dimensional NumPy array, how to convert this to the standard C++ `std::vector`, and how to return a one-dimensional NumPy array. Note that the interface generated using pybind11 is so flexible that it even accepts list inputs on the Python side.

## [04_numpy-2D_cpp-vector](04_numpy-2D_cpp-vector)

One function `length`. This function accepts a 'matrix' in which comprises a list of 2-D position vectors, as rows. The result is again a 'matrix' with for each row the "x" and "y" position, and the length of the 2-D position vector.

## [05_numpy-2D_cpp-eigen](05_numpy-2D_cpp-eigen)

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

## [06_class-numpy-eigen](06_class-numpy-eigen)

A custom `CustomVectorXd` class with one function `mul`. This class uses the Eigen library. It also includes a default argument.

Furthermore, this example has a function `trans` (totally unrelated to the custom `CustomVectorXd` class). It's purpose is to show how to return a new `Eigen::VectorXi` (or NumPy-array).

## [07_cpp-overload-scalar](07_cpp-overload-scalar)

One overloaded function `mul`. This function acts 'differently' if it is called with `int` arguments or `double` arguments. Notice that the default behavior of pybind11 is quite robust. When calling the function with one `int` and one `double` argument, the module will choose the `double` version of `mul` (and will cast the `int` argument to a `double`).

To compile, make sure that the C++14 standard is used, for example by including `-std=c++14` as compiler argument.

## [08_cpp-overload-eigen](08_cpp-overload-eigen)

Similar to the [previous example](#08cpp-overload-eigen), but with Eigen arguments (i.e. NumPy arguments from the Python side).

To compile, make sure that the C++14 standard is used.

## [09_numpy_cpp-custom-matrix](09_numpy_cpp-custom-matrix)

This example includes a custom matrix class in C++ (in `matrix.h`). This class is coupled to a NumPy-array using a simple interface (in `pybind_matrix.h`). Consequently the functions (in `example.cpp`) do not necessitate any special wrapper code.

See also [this](http://stackoverflow.com/questions/42645228/cast-numpy-array-to-from-custom-c-matrix-class-using-pybind11) discussion of Stack Overflow.

## [10_enum](10_enum)

This example features a way to interface with an enumerator in C++. In principle the interface is straightforward but warrants a 'trick'. Here a submodule is used to be able to interact with the enumerator in the same way as in C++.

## [11_class-parent-child](11_class-parent-child)

This example contains a classical example where one or more classes are derived from a certain parent or template. This particular example contains two animals, a `Dog` and a `Cat`, that are both derived from a generic `Animal` class. There is a function `talk` that accepts the generic `Animal` and thus any of the derived classes. 

This particular case requires more involved interface, as is described in [the documentation](http://pybind11.readthedocs.io/en/stable/advanced/classes.html).

