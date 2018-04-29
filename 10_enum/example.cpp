
#include <string>
#include <iostream>
#include <pybind11/pybind11.h>

// ------------------
// regular C++ header
// ------------------

struct Type {
  enum Value {
    Cat,
    Dog,
  };
};

// ----------------
// regular C++ code
// ----------------

void whichAnimal(int animal)
{
  if      ( animal == Type::Cat ) std::cout << "Cat"     << std::endl;
  else if ( animal == Type::Dog ) std::cout << "Dog"     << std::endl;
  else                            std::cout << "Unknown" << std::endl;
}

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example, m)
{
  py::module sm = m.def_submodule("Type", "Type enumerator");

  py::enum_<Type::Value>(sm, "Type")
    .value("Cat", Type::Cat)
    .value("Dog", Type::Dog)
    .export_values();

  m.def("whichAnimal", &whichAnimal, py::arg("animal"));
}
