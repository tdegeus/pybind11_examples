
# Overview

From both the Python and the C++ side, this example features a module `example` with one function `modify`. It takes a nested list, multiplies all entries by two, and returns it as a nested listed of doubles.

From the implementation perspective, the purpose of this example is to show how to have a function accept a list, how to convert this to the standard C++ `std::vector`, and how to return a new list.

# Compiling

```bash
c++ -O3 -shared -std=gnu++11 -I ../pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

The example can now be run (from this folder) by

```bash
python3 test.py
```

>   To run with Python 2, simply replace the two occurrences of "python3" above with "python".
