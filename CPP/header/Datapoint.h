#pragma once

#include <pybind11/numpy.h>
namespace py = pybind11;

struct Datapoint {

    Datapoint() {}
    Datapoint(py::array_t<float> data_, int label_) :
        data(data_), label(label_) { }

    py::array_t<float> data;
    int label;

};