#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <vector>

// -------------
// pure C++ code
// -------------

std::vector<double> length ( std::vector<double> x , std::vector<double> y )
{

  std::vector<double> output(x.size()*3);

  for ( int i=0 ; i<(int)x.size() ; i++ ) {
    output[i*3+0] = x[i];
    output[i*3+1] = y[i];
    output[i*3+2] = pow(x[i]*y[i],.5);
  }

  return output;

}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

// wrap C++ function with NumPy array IO
py::array py_length(py::array_t<double, py::array::c_style | py::array::forcecast> array) {

  // check input dimensions
  if ( array.ndim()     != 2 )
    throw std::runtime_error("Input should be 2-D NumPy array");
  if ( array.shape()[1] != 2 )
    throw std::runtime_error("Input should have size [N,2]");

  // allocate std::vector (to pass to the C++ function)
  std::vector<double> x(array.shape()[0]);
  std::vector<double> y(array.shape()[0]);

  // copy py::array -> std::vector
  for ( int i=0 ; i<(int)array.shape()[0] ; i++ ) {
    x[i] = array.data()[i*array.shape()[1]+0];
    y[i] = array.data()[i*array.shape()[1]+1];
  }

  // call pure C++ function
  std::vector<double> result = length(x,y);

  // return 2-D NumPy array
  return py::array(py::buffer_info(
    result.data(),                           /* data as contiguous array  */
    sizeof(double),                          /* size of one scalar        */
    py::format_descriptor<double>::format(), /* data type                 */
    2,                                       /* number of dimensions      */
    { array.shape()[0] , 3 },                /* shape of the matrix       */
    { sizeof(double)*3 , sizeof(double) }    /* strides for each axis     */
  ));

}

// wrap as Python module
PYBIND11_PLUGIN(example) {

  py::module m("example", "pybind11 example plugin");

  m.def("length", &py_length, "Calculate the length of an array of vectors");

  return m.ptr();

}

