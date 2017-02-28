#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

// ----------------
// Regular C++ code
// ----------------

// multiply all entries by 2.0
// input:  std::vector ([...]) (read only)
// output: std::vector ([...]) (new copy)
std::vector<double> modify(const std::vector<double>& inputVector) {

  std::vector<double> outputVector;

  std::transform(
    inputVector.begin(),
    inputVector.end(),
    std::back_inserter(outputVector),
    [](double x) -> double { return 2.*x; }
  );

  return outputVector;

}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_PLUGIN(example) {
  py::module m("example", "pybind11 example plugin");
  m.def("modify", &modify, "Multiply all entries of a list by 2.0");
  return m.ptr();
}

