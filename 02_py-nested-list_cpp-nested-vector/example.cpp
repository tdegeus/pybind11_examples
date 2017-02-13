#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

// ----------------
// Regular C++ code
// ----------------

// description: multiply all entries by 2.0
// input:       nested std::vector ([[...],[...]]) (not modified)
// output:      nested std::vector ([[...],[...]]) (new copy)
std::vector<std::vector<double>> modify(std::vector<std::vector<double>>& inputVector) {

  std::vector<std::vector<double>> outputVector;

  std::transform(
    inputVector.begin(),
    inputVector.end(),
    std::back_inserter(outputVector),
    [](const std::vector<double> &iv) {
      std::vector<double> dv;
      std::transform(iv.begin(), iv.end(), std::back_inserter(dv), [](double x) -> double { return 2.*x; });
      return dv;
    }
  );

  return outputVector;

}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_PLUGIN(example) {
    py::module m("example", "pybind11 example plugin");

    m.def("modify", &modify, "Multiply all entries of a nested list by 2.0");

    return m.ptr();
}

