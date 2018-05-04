
#include <string>
#include <iostream>
#include <pybind11/pybind11.h>

// ------------------
// regular C++ header
// ------------------

// parent class
class Animal
{
public:
  virtual std::string talk(int n_times) = 0;
};

// derived class
class Dog : public Animal
{
public:
  std::string talk(int n_times) override;
};

// derived class
class Cat : public Animal
{
public:
  std::string talk(int n_times) override;
};

// function that takes the parent and all derived classes
std::string talk(Animal &animal, int n_times=1);

// ----------------
// regular C++ code
// ----------------

inline std::string Dog::talk(int n_times)
{
  std::string result;

  for ( int i = 0 ; i < n_times ; ++i )
    result += "woof! ";

  return result;
}


inline std::string Cat::talk(int n_times)
{
  std::string result;

  for ( int i = 0 ; i < n_times ; ++i )
    result += "meow! ";

  return result;
}


std::string talk(Animal &animal, int n_times)
{
  return animal.talk(n_times);
}

// -----------------------------
// Python interface - trampoline
// -----------------------------

class PyAnimal : public Animal
{
public:

  // inherit the constructors
  using Animal::Animal;

  // trampoline (one for each virtual function)
  std::string talk(int n_times) override {
    PYBIND11_OVERLOAD_PURE(
      std::string, /* Return type */
      Animal,      /* Parent class */
      talk,        /* Name of function in C++ (must match Python name) */
      n_times      /* Argument(s) */
    );
  }
};

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(example, m)
{
  py::class_<Animal, PyAnimal>(m, "Animal")
    .def(py::init<>())
    .def("talk", &Animal::talk);

  py::class_<Dog, Animal>(m, "Dog")
    .def(py::init<>());

  py::class_<Cat, Animal>(m, "Cat")
    .def(py::init<>());

  m.def("talk", &talk, py::arg("animal") ,py::arg("n_times")=1);
}
