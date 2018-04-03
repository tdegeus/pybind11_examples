#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <Eigen/LU>

// ------------------
// regular C++ header
// ------------------

// a custom vector-class, with one function "mul"
class CustomVectorXd
{
private:

  Eigen::VectorXd m_data;

public:

  CustomVectorXd(const Eigen::VectorXd &data);

  Eigen::VectorXd mul(double factor=1.);

};

// ----------------
// regular C++ code
// ----------------

// class-constructor: store the input "Eigen::VectorXd"
CustomVectorXd::CustomVectorXd(const Eigen::VectorXd &data) : m_data(data)
{
}

// return the custom vector, multiplied by a factor
Eigen::VectorXd CustomVectorXd::mul(double factor)
{
  return factor*m_data;
}

// a function that has nothing to do with the class
// the point is to show how one can return a copy "Eigen::VectorXd"
Eigen::VectorXi trans(const Eigen::VectorXi& array)
{
  auto N = array.size();

  Eigen::VectorXi out(N);

  for ( auto i = 0 ; i < N ; ++i )
    out[array.size()-i-1] = array[i];

  return out;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example,m)
{
  m.doc() = "pybind11 example plugin";

  m.def("trans", &trans);

  py::class_<CustomVectorXd>(m, "CustomVectorXd")
  .def(py::init<Eigen::VectorXd>())
  .def("mul", &CustomVectorXd::mul,pybind11::arg("factor")=1.)
  .def("__repr__",
    [](const CustomVectorXd &a) {
      return "<example.CustomVectorXd>";
    }
  );
}
