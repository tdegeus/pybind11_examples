# pybind11_examples

<!-- MarkdownTOC -->

- [Introduction](#introduction)
- [Cloning this repository](#cloning-this-repository)
- [Dependencies](#dependencies)
    - [Eigen](#eigen)
    - [CMake](#cmake)

<!-- /MarkdownTOC -->

# Introduction

The power of [`pybind11`](https://github.com/pybind/pybind11) is captured by the following citation from the [`pybind11`](https://github.com/pybind/pybind11) readme:

>   `pybind11` is a lightweight header-only library that exposes C++ types in Python and vice versa, mainly to create Python bindings of existing C++ code. Its goals and syntax are similar to the excellent `Boost.Python` library by David Abrahams ...
>
>   The main issue with `Boost.Python` - and the reason for creating such a similar project — is `Boost`. `Boost` is an enormously large and complex suite of utility libraries that works with almost every C++ compiler in existence. ... Now that C++11-compatible compilers are widely available, this heavy machinery has become an excessively large and unnecessary dependency.

This repository contains several examples for the usage of `pybind11`. Even though the [online documentation](http://pybind11.readthedocs.io) provided by the developers of `pybind11` makes the usage of it relatively straightforward, several examples - such as provided here - make `pybind11` even easier to use. These example are meant for you to start quicker with `pybind11`. They are however by no means exhaustive, and do not always provide the optimal choice. Therefore it is highly advisable to **think for yourself**. Furthermore, contributions with similar simple examples (or by further improving existing examples) are highly welcomed.

To give credit where credit is due:

*   The creators of [`pybind11`](https://github.com/pybind/pybind11) have done a great job! It is really easy to use, and very lightweight. Also the [documentation](http://pybind11.readthedocs.io) is already quite complete.

*   The examples made available by [Cliburn Chan and Janice McCarthy, at Duke University](http://people.duke.edu/~ccc14/sta-663-2016/18G_C++_Python_pybind11.html) have been of enormous help. Please also read their [documentation](http://people.duke.edu/~ccc14/sta-663-2016/18G_C++_Python_pybind11.html).

Note that there are also test-cases included in the `pybind11` [repository](https://github.com/pybind/pybind11), but these are not very insightful when you are new to `pybind11`.

# Cloning this repository

The `pybind11` module (which is header only!) is included as a submodule of this repository. This requires some attention when cloning this project. There are two options. The simplest one is:

```bash
git clone --recursive https://github.com/tdegeus/pybind11_examples.git
```

This will download the submodule up to the version that is used in this project. To update to the latest commit of the submodule itself:

```bash
git submodule update --remote
```

Alternatively, one could directly download the submodule from the source:

```bash
git clone https://github.com/tdegeus/pybind11_examples.git
cd pybind11_examples
git submodule init
git submodule update
```

# Dependencies

## Eigen

The [`Eigen`](http://eigen.tuxfamily.org)-library is used in some of the `NumPy` examples. From these examples is can be observed that through `pybind11`, `Eigen` and `NumPy` are really handshake modules. Almost no code is needed to create the C++/Python interface. Although it must be said that mostly copies are passed, some attention is needed if one wants to pass purely by reference.

[`Eigen`](http://eigen.tuxfamily.org) does not need installation because it is also header-only. One just needs to download the files and include the headers at compile time.

*   For macOS with homebrew:

    ```bash
    brew install eigen
    ```

    Then, compile with

    ```bash
    -I /usr/local/Cellar/eigen/3.3.1/include/eigen3
    ```

    (or something similar specialized to your installation). Note that `CMake` can find `Eigen` independently (see below).

## CMake

>   The example are to a large degree independent. This means that each of the examples has to be compiled independently.

### Basic usage

`pybind11` applications can be compiled very easy using `CMake`. If one adds `pybind11` as a sub-folder of the `src` directory, one can use for example the following `CMakeLists.txt` file:

```bash
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

### Using `Eigen`

When `Eigen` is 'installed' it can be easily included by adding the following in `CMakeLists.txt`:

```bash
find_package( PkgConfig )
pkg_check_modules( EIGEN3 REQUIRED eigen3 )
include_directories( ${EIGEN3_INCLUDE_DIRS} )
```

### Using the `C++14` standard

The `C++14` standard (which is needed for the *overload* examples) can be used by including

```bash
set(CMAKE_CXX_STANDARD 14)
```

in `CMakeLists.txt`.
