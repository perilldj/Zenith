#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../header/Test.h"

namespace py = pybind11;

PYBIND11_MODULE(Zenith, handle) {

    handle.def("Bruh",  &Test::Bruh);

}