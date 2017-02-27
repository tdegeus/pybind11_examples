
# Overview

From both the Python and the C++ side, this example features a module `example` with one function `length`. This function accepts a 'matrix' in which comprises a list of 2-D position vectors, as rows. The result is again a 'matrix' with for each row the "x" and "y" position, and the length of the 2-D position vector.

From an implementation perspective, the purpose of this example is how to have a function accept an arbitrary NumPy-array, how to convert this to the C++-standard `std::vector`, and how to return an arbitrary NumPy-array.

# Compiling

The compiling instructions are generated from `CMakeLists.txt`, and then compiled using

```bash
cmake .
make
```

Compiling can also be performed directly. To compile both the `pybind11` headers and the `Eigen` headers have to be included:

```bash
c++ -O3 -shared -std=gnu++11 -I ../pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

The example can now be run (from this folder) by

```bash
python3 test.py
```

>   To run with Python 2, simply replace the two occurrences of "python3" above with "python". To modify the `cmake` instructions find more [online](http://pybind11.readthedocs.io/en/master/compiling.html?highlight=cmake)
