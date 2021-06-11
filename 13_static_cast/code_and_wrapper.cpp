#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

// ------------------
// regular C++ header
// ------------------

namespace mymodule {

class Foo
{
public:

    Foo() = default;

    template <class T>
    T bar(const T& a) const
    {
        T ret = a;
        for (auto& i : ret) {
            i *= 2.0;
        }
        return ret;
    }

    template <class T>
    T bar(const T& a, double f) const
    {
        T ret = a;
        for (auto& i : ret) {
            i *= f;
        }
        return ret;
    }

};

} // namespace mymodule

// ----------------
// Python interface
// ----------------

namespace py = pybind11;

PYBIND11_MODULE(mymodule, m)
{
    py::class_<mymodule::Foo>(m, "Foo")
        .def(py::init<>())

        .def("bar",
             static_cast<std::vector<double> (mymodule::Foo::*)(const std::vector<double>&) const>(&mymodule::Foo::bar),
             py::arg("a"))

        .def("bar",
             static_cast<std::vector<double> (mymodule::Foo::*)(const std::vector<double>&, double) const>(&mymodule::Foo::bar),
             py::arg("a"),
             py::arg("f"));
}
