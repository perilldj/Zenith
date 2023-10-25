#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../header/Matrix.h"
#include "../header/Testing.h"

namespace py = pybind11;

PYBIND11_MODULE(Zenith, handle) {

    handle.def("RunTest", &Testing::RunTest);

}