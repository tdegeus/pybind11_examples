#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/LU>

// ----------------
// regular C++ code
// ----------------

Eigen::MatrixXd inv(Eigen::MatrixXd xs) {
    return xs.inverse();
}

double det(Eigen::MatrixXd xs) {
    return xs.determinant();
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_PLUGIN(example) {
    pybind11::module m("example", "simple example module");
    m.def("inv", &inv);
    m.def("det", &det);
    return m.ptr();
}
