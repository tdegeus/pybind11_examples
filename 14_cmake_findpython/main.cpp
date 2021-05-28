#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

template <class T>
inline T foo(T& arg)
{
    T ret = arg;

    for (auto& i : ret) {
        i *= 2;
    }

    return ret;
}

PYBIND11_MODULE(mymodule, m)
{
    m.doc() = "Module description";
    m.def("foo", &foo<std::vector<int>>, "Function description", py::arg("arg"));
}
