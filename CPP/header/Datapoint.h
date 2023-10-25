#pragma once

#include <pybind11/numpy.h>
namespace py = pybind11;

struct Datapoint {

    Datapoint() {}
    Datapoint(py::array_t<float> data_, int label_) {
        for(int i = 0; i < data_.size(); i++)
            data.push_back(data_.at(i));
    }

    std::vector<float> data;
    int label;

};