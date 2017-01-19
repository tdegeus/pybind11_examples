
# Overview

From both the Python side as well as from the C++ side, this example features a module `example` with two functions `det` and `inv`. This function uses the [`Eigen`](http://eigen.tuxfamily.org/index.php?title=Main_Page) library. As observed this trivially results in a wrapper that can accept NumPy-arrays.

# Compiling

To compile both the `pybind11` headers and the `Eigen` headers have to be include:

```bash
c++ -O3 -shared -std=gnu++11 -I /path/to/eigen -I ../pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

For example on macOS with homebrew:

```bash
c++ -O3 -shared -std=gnu++11 -I /usr/local/Cellar/eigen/3.3.1/include/eigen3 -I ../pybind11/include `python3-config --cflags --ldflags --libs` example.cpp -o example.so -fPIC
```

The example can now be run (from this folder) by

```bash
python3 test.py
```

>   To run with Python 2, simply replace the two occurrences of "python3" above with "python".
