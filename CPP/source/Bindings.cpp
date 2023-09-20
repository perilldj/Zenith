#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../header/Matrix.h"

namespace py = pybind11;

PYBIND11_MODULE(Zenith, handle) {

    py::class_<Matrix> ( handle, "Matrix" )

        .def(py::init<int, int>())

        .def("get", &Matrix::Get)
        .def("set", &Matrix::Set)

    ;

}