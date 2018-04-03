#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <vector>

// -------------
// pure C++ code
// -------------

std::vector<double> length(const std::vector<double>& pos)
{
  size_t N = pos.size() / 2;

  std::vector<double> output(N*3);

  for ( size_t i = 0 ; i < N ; ++i ) {
    output[i*3+0] = pos[i*2+0];
    output[i*3+1] = pos[i*2+1];
    output[i*3+2] = std::pow(pos[i*2+0]*pos[i*2+1],.5);
  }

  return output;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

// wrap C++ function with NumPy array IO
py::array py_length(py::array_t<double, py::array::c_style | py::array::forcecast> array)
{
  // check input dimensions
  if ( array.ndim()     != 2 )
    throw std::runtime_error("Input should be 2-D NumPy array");
  if ( array.shape()[1] != 2 )
    throw std::runtime_error("Input should have size [N,2]");

  // allocate std::vector (to pass to the C++ function)
  std::vector<double> pos(array.size());

  // copy py::array -> std::vector
  std::memcpy(pos.data(),array.data(),array.size()*sizeof(double));

  // call pure C++ function
  std::vector<double> result = length(pos);

  ssize_t              ndim    = 2;
  std::vector<ssize_t> shape   = { array.shape()[0] , 3 };
  std::vector<ssize_t> strides = { sizeof(double)*3 , sizeof(double) };

  // return 2-D NumPy array
  return py::array(py::buffer_info(
    result.data(),                           /* data as contiguous array  */
    sizeof(double),                          /* size of one scalar        */
    py::format_descriptor<double>::format(), /* data type                 */
    ndim,                                    /* number of dimensions      */
    shape,                                   /* shape of the matrix       */
    strides                                  /* strides for each axis     */
  ));
}

// wrap as Python module
PYBIND11_MODULE(example,m)
{
  m.doc() = "pybind11 example plugin";

  m.def("length", &py_length, "Calculate the length of an array of vectors");
}
