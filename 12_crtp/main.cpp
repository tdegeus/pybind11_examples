#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

template <class Derived>
class BaseImpl
{
public:

    template <class T>
    T myfunc(const T& t)
    {
        return static_cast<Derived*>(this)->myfunc_impl(t);
    }

private:
    template <class T>
    T myfunc_impl(const T& t)
    {
        T ret = t;
        for (auto& i : ret) {
            i *= 2.0;
        }
        return ret;
    }
};

class Base : public BaseImpl<Base>
{
public:
    Base() = default;

private:
    friend class BaseImpl<Base>;
};

class Derived : public BaseImpl<Derived>
{
public:
    Derived() = default;

private:
    template <class T>
    T myfunc_impl(const T& t)
    {
        T ret = t;
        for (auto& i : ret) {
            i *= 3.0;
        }
        return ret;
    }

private:
    friend class BaseImpl<Derived>;
};

template <class T, class M>
auto registerBaseImpl(M& self)
{
    self.def(py::init<>())
        .def("myfunc", &T::template myfunc<std::vector<double>>);
}

PYBIND11_MODULE(mymodule, m)
{
    m.doc() = "CRTP example";

    py::class_<BaseImpl<Base>> BaseBase(m, "BaseBase");
    py::class_<BaseImpl<Derived>> BaseDerived(m, "BaseDerived");

    registerBaseImpl<BaseImpl<Base>>(BaseBase);
    registerBaseImpl<BaseImpl<Derived>>(BaseDerived);

    py::class_<Base, BaseImpl<Base>>(m, "Base")
        .def(py::init<>());

    py::class_<Derived, BaseImpl<Derived>>(m, "Derived")
        .def(py::init<>());
}
