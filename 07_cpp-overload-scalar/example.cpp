#include <pybind11/pybind11.h>
#include <iostream>

// ----------------
// regular C++ code
// ----------------

double mul(double a, double b)
{
  std::cout << "Double" << std::endl;
  return a*b;
}

int mul(int a, int b)
{
  std::cout << "Int" << std::endl;
  return a*b;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example,m)
{
  m.doc() = "pybind11 example plugin";

  m.def("mul", py::overload_cast<int   ,int   >(&mul) );
  m.def("mul", py::overload_cast<double,double>(&mul) );
}
