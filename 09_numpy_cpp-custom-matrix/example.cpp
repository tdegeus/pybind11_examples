
#include "matrix.h"
#include "pybind_matrix.h"

// ----------------
// regular C++ code
// ----------------

Matrix<double> mul ( Matrix<double> A, Matrix<double> B )
{
  if ( A.shape()!=B.shape() )
    throw std::length_error("Matrix 'A' and 'B' are inconsistent");

  Matrix<double> ret(A.shape());

  for ( int i=0 ; i<A.size() ; i++ )
    ret[i] = A[i]*B[i];

  return ret;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_PLUGIN(example) {
    pybind11::module m("example", "simple example module");
    m.def("mul", &mul );
    return m.ptr();
}
