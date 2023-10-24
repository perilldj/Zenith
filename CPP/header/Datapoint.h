#pragma once

#include <pybind11/numpy.h>
namespace py = pybind11;

struct Datapoint {

    Datapoint() {}
    Datapoint(py::array_t<float> data, int label) : 

    py::array_t<float> data;
    int label;

};