# pybind11_examples

From the [`pybind11` readme](https://github.com/pybind/pybind11):

>   `pybind11` is a lightweight header-only library that exposes C++ types in Python and vice versa, mainly to create Python bindings of existing C++ code. Its goals and syntax are similar to the excellent `Boost.Python` library by David Abrahams ...
>
>   The main issue with `Boost.Python` - and the reason for creating such a similar project — is `Boost`. `Boost` is an enormously large and complex suite of utility libraries that works with almost every C++ compiler in existence. ... Now that C++11-compatible compilers are widely available, this heavy machinery has become an excessively large and unnecessary dependency.

This repository contains several examples for the usage of `pybind11`. Even though the [online documentation](http://pybind11.readthedocs.io) provided by the developers of `pybind11` makes the usage of it relatively straightforward, several examples - such as provided here - make `pybind11` even easier to use. These example are meant for you to start quicker with `pybind11`. They are however by no means exhaustive, and do not always provide the optimal choice. Therefore it is highly advisable to 'think for yourself'. Furthermore, contributions of similar simple examples are highly welcomed.

>   Note that there are also test-cases included in the [`pybind11` repository](https://github.com/pybind/pybind11), but these are not very insightful when you are new to `pybind11`.

# Cloning the examples

The `pybind11` module (which is header only!) is included as a submodule of this repository. This asks for a little bit more attention when cloning this project. There are two options. The simplest one is

```bash
git clone --recursive https://github.com/tdegeus/pybind11_examples.git
```

This will download the submodule up to the version that is used in this project. To directly download the submodule from the source use


```bash
git clone https://github.com/tdegeus/pybind11_examples.git
cd pybind11_examples
git submodule init
git submodule update
```

