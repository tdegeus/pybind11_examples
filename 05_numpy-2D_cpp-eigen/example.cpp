#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/LU>

// N.B. this would equally work with Eigen-types that are not predefined. For example replacing
// all occurrences of "Eigen::MatrixXd" with "MatD", with the following definition:
//
//  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> MatD;

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
