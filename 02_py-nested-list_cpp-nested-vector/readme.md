
# Overview

From both the Python side as well as from the C++ side, this example features a module `example` with one function `modify`. It takes a nested list, multiplies all entries by two, and returns it as a nested listed of doubles.

From an implementation perspective, the purpose of this example is to show how to have a function accept an nested list, how to convert this to the standard C++ `std::vector`, and how to return a nested array.

# Compiling

```bash
c++ -O3 -shared -std=gnu++11 -I ../pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

The example can now be run (from this folder) by

```bash
python3 test.py
```

>   To run with Python 2, simply replace the two occurrences of "python3" above with "python".
