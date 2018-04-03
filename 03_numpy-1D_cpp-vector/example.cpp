#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <vector>

// -------------
// pure C++ code
// -------------

std::vector<int> multiply(const std::vector<double>& input)
{
  std::vector<int> output(input.size());

  for ( size_t i = 0 ; i < input.size() ; ++i )
    output[i] = 10*static_cast<int>(input[i]);

  return output;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

// wrap C++ function with NumPy array IO
py::array_t<int> py_multiply(py::array_t<double, py::array::c_style | py::array::forcecast> array)
{
  // allocate std::vector (to pass to the C++ function)
  std::vector<double> array_vec(array.size());

  // copy py::array -> std::vector
  std::memcpy(array_vec.data(),array.data(),array.size()*sizeof(double));

  // call pure C++ function
  std::vector<int> result_vec = multiply(array_vec);

  // allocate py::array (to pass the result of the C++ function to Python)
  auto result        = py::array_t<int>(array.size());
  auto result_buffer = result.request();
  int *result_ptr    = (int *) result_buffer.ptr;

  // copy std::vector -> py::array
  std::memcpy(result_ptr,result_vec.data(),result_vec.size()*sizeof(int));

  return result;
}

// wrap as Python module
PYBIND11_MODULE(example,m)
{
  m.doc() = "pybind11 example plugin";

  m.def("multiply", &py_multiply, "Convert all entries of an 1-D NumPy-array to int and multiply by 10");
}
