cmake_minimum_required(VERSION 3.5.0)
project(pybind_test VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
add_subdirectory(pybind11)

pybind11_add_module(Zenith
                        CPP/source/Bindings.cpp
                        CPP/source/Matrix.cpp
                        CPP/source/MaxPooling.cpp
                        CPP/source/NMath.cpp
                        CPP/source/Testing.cpp
                        CPP/source/Network.cpp
                        CPP/source/Dense.cpp
                        CPP/source/Flatten.cpp
)