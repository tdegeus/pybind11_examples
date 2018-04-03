#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/LU>
#include <iostream>

// ----------------
// regular C++ code
// ----------------

Eigen::MatrixXd mul(const Eigen::MatrixXd &xs, double fac)
{
    std::cout << "Double" << std::endl;
    return fac*xs;
}

Eigen::MatrixXi mul(const Eigen::MatrixXi &xs, int    fac)
{
    std::cout << "Int" << std::endl;
    return fac*xs;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example,m)
{
  m.doc() = "pybind11 example plugin";

  // N.B. the order here is crucial, in the reversed order every "int" is converted to a "double"
  m.def("mul", py::overload_cast<const Eigen::MatrixXi &,int   >(&mul) );
  m.def("mul", py::overload_cast<const Eigen::MatrixXd &,double>(&mul) );
}
