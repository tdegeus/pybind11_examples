
# Overview

From both the Python and the C++ side, this example features a module `example` with one function `mul` that multiplies two input numbers. The key point of this example that this function is overloaded: there are two functions, one for `int` arguments and one for `double` arguments. 

See [pybind11 documentation](http://pybind11.readthedocs.io/en/master/classes.html#overloaded-methods).

# Compiling

The compiling instructions are generated from `CMakeLists.txt`, and then compiled using

```bash
cmake .
make
```

Compiling can also be performed directly. To compile the `pybind11` headers have to be included. In addition we need `C++14` compatibility:

```bash
c++ -O3 -shared -std=gnu++14 -I ./pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

The example can now be run (from this folder) by

```bash
python3 test.py
```

>   To run with Python 2, simply replace the two occurrences of "python3" above with "python". To modify the `cmake` instructions find more [online](http://pybind11.readthedocs.io/en/master/compiling.html?highlight=cmake)
