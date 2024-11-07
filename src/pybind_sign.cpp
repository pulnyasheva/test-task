#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "sign.h"

namespace py = pybind11;

PYBIND11_MODULE(signs, m) {
    py::class_<Coordinates>(m, "Coordinates")
        .def(py::init<double, double>())
        .def_readwrite("longitude", &Coordinates::longitude)
        .def_readwrite("latitude", &Coordinates::latitude);

    py::class_<Sign>(m, "Sign")
        .def(py::init<>())
        .def(py::init<std::string, unsigned int, const Coordinates&>())
        .def_readwrite("name", &Sign::name)
        .def_readwrite("id", &Sign::id)
        .def_readwrite("coordinates", &Sign::coordinates);

    py::class_<SignDatabase>(m, "SignDatabase")
        .def(py::init<>())
        .def("add_sign", &SignDatabase::add_sign)
        .def("remove_sign", &SignDatabase::remove_sign)
        .def("find_sign", &SignDatabase::find_sign)
        .def("add_signs", &SignDatabase::add_signs);
}
