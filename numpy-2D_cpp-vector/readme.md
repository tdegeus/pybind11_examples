
# Overview

From both the Python side as well as from the C++ side, this examples features a module `example` with one function `multipy`. It converts the entries from a one-dimensional array to integers, and then multiplies these entries by 10.

From an implementation perspective, the purpose of this example is how to have a function accept an 1-D NumPy-array, how to convert this to the C++-standard `std::vector`, and how to return an 1-D NumPy-array. As if observed in the test case, the `pybind11`-interface is so flexible that it even accepts list inputs.

# Compiling

```bash
c++ -O3 -shared -std=gnu++11 -I ../pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

The example can now be run (from this folder) by

```bash
python3 test.py
```

>   To run with Python 2, simply replace the two occurrences of "python3" above with "python".
