#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/LU>
#include <iostream>

// ----------------
// regular C++ code
// ----------------

Eigen::MatrixXd mul(Eigen::MatrixXd xs, double fac) {
    std::cout << "Double" << std::endl;
    return fac*xs;
}

Eigen::MatrixXi mul(Eigen::MatrixXi xs, int    fac) {
    std::cout << "Int" << std::endl;
    return fac*xs;
}


// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_PLUGIN(example) {
    pybind11::module m("example", "simple example module");
    m.def("mul", py::overload_cast<Eigen::MatrixXd,double>(&mul) );
    m.def("mul", py::overload_cast<Eigen::MatrixXi,int   >(&mul) );
    return m.ptr();
}
