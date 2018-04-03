#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

// ----------------
// Regular C++ code
// ----------------

// multiply all entries by 2.0
// input:  nested std::vector ([[...],[...]]) (read-only)
// output: nested std::vector ([[...],[...]]) (new copy)
std::vector<std::vector<double>> modify(const std::vector<std::vector<double>>& input)
{
  std::vector<std::vector<double>> output;

  std::transform(
    input.begin(),
    input.end(),
    std::back_inserter(output),
    [](const std::vector<double> &iv) {
      std::vector<double> dv;
      std::transform(iv.begin(), iv.end(), std::back_inserter(dv), [](double x) -> double { return 2.*x; });
      return dv;
    }
  );

  return output;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example,m)
{
  m.doc() = "pybind11 example plugin";

  m.def("modify", &modify, "Multiply all entries of a nested list by 2.0");
}
