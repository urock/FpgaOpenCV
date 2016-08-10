cmake_minimum_required(VERSION 3.5)
project(generalizedNet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Layer.hpp Network.cpp Network.hpp GradDescent.cpp GradDescent.hpp Parser.cpp Parser.hpp Data.cpp Data.hpp Convolution.cpp Convolution.hpp Subsampling.hpp MaxPooling.cpp MaxPooling.hpp Subsampling.cpp)
add_executable(generalizedNet ${SOURCE_FILES})