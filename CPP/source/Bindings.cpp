#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../header/Matrix.h"
#include "../header/Testing.h"

namespace py = pybind11;

PYBIND11_MODULE(Zenith, handle) {

    handle.def("RunTest", &Testing::RunTest);

    py::enum_<EInitialization>(handle, "EInitialization")
        .value("Random",  EInitialization::Random)
        .value("Kaiming", EInitialization::Kaiming)
        .value("Xavier",  EInitialization::Xavier)
        .export_values()
    ;

    py::enum_<EDistribution>(handle, "EDistribution")
        .value("Uniform",  EDistribution::Uniform)
        .value("Normal",   EDistribution::Normal)
        .export_values()
    ;

    py::enum_<EActivation>(handle, "EActivation")
        .value("Identity",  EActivation::Identity)
        .value("Sigmoid",   EActivation::Sigmoid)
        .value("Tanh",      EActivation::Tanh)
        .value("ReLU",      EActivation::ReLU)
        .value("LeakyReLU", EActivation::LeakyReLU)
        .value("SiLU",      EActivation::SiLU)
        .value("Softplus",  EActivation::Softplus)
        .value("Softmax",   EActivation::Softmax)
        .export_values()
    ;

    py::enum_<ECost>(handle, "ECost")
        .value("MSE",           ECost::MSE)
        .value("CrossEntropy",  ECost::CrossEntropy)
        .export_values()
    ;

    py::enum_<ELayer>(handle, "ELayer")
        .value("Dense",  ELayer::Dense)
        .export_values()
    ;

    py::class_<Network> ( handle, "Network" )
        
        .def(py::init<>())

        .def_readwrite("DoLearningRateDecay",   &Network::learningRateDecay)
        .def_readwrite("LearningRate",          &Network::initialLearningRate)
        .def_readwrite("DecayRate",             &Network::decayRate)

        .def_readwrite("Epochs",                &Network::totalEpochCount)
        .def_readwrite("BatchSize",             &Network::batchSize)
        .def_readwrite("TrainingTestingSplit",  &Network::trainingTestingSplit)

        .def_readwrite("Cost",                  &Network::networkCost)
        .def_readwrite("Initializer",           &Network::networkInitializer)
        .def_readwrite("Distribution",          &Network::networkDistribution)

        .def("Dense",           &Network::Dense)
        .def("MaxPooling",      &Network::MaxPooling)
        .def("Flatten",         &Network::Flatten)

        .def("AddDatapoint",    &Network::AddDatapoint)
        .def("SetInputShape",   &Network::SetInputShape)
        .def("Compile",         &Network::Compile)
        .def("Train",           &Network::Train)

        .def_readonly("TrainingCost",        &Network::d_training_cost)
        .def_readonly("TrainingAccuracy",    &Network::d_training_accuracy)
        .def_readonly("TestingCost",         &Network::d_testing_cost)
        .def_readonly("TestingAccuracy",     &Network::d_testing_accuracy)

    ;

    /*
    
        py::class_<Network> ( handle, "Network" )
    
        .def(py::init<>())

        .def_readwrite("InterEpochTracking", &Network::interEpochTracking)
        .def_readwrite("LearningRateDecay",  &Network::learningRateDecay)

        .def_readonly("train_cost", &Network::train_cost)
        .def_readonly("train_average", &Network::train_average)
        .def_readonly("test_cost", &Network::test_cost)
        .def_readonly("test_average", &Network::test_average)

        .def_readwrite("BatchSize",     &Network::batchSize)
        .def_readwrite("Epochs",        &Network::epochs)
        .def_readwrite("LearningRate",  &Network::learningRate)
        .def_readwrite("DecayRate",     &Network::decayRate)

        .def_readwrite("Cost",          &Network::networkCost)
        .def_readwrite("Initializer",   &Network::initializer)
        .def_readwrite("Distribution",  &Network::distribution)

        .def("TrainNetwork",           &Network::TrainNetwork)
        .def("TestNetwork",            &Network::TestNetwork)
        .def("Evaluate",               &Network::Evaluate)
        .def("AddTrainingDatapoint",   &Network::AddTrainingDatapoint)
        .def("AddTestingDatapoint",    &Network::AddTestingDatapoint)
        .def("Dense",                  &Network::Dense)
        .def("Conv2D",                 &Network::Conv2D)
        .def("MaxPooling",             &Network::MaxPooling)
        .def("DefineInputShape",       &Network::DefineInputShape)
        .def("Compile",                &Network::Compile)

    ;

    */

}