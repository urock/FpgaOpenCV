cmake_minimum_required(VERSION 3.5)
project(generalizedNet)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lopencv_highgui")

set(SOURCE_FILES main.cpp Layer.hpp Network.cpp Network.hpp GradDescent.cpp GradDescent.hpp Parser.cpp Parser.hpp Data.cpp Data.hpp layers/Convolution.cpp layers/Convolution.hpp layers/Subsampling.hpp layers/MaxPooling.cpp layers/MaxPooling.hpp layers/Subsampling.cpp Layer.cpp Teacher.cpp Teacher.hpp Converter.cpp Converter.hpp)
add_executable(generalizedNet ${SOURCE_FILES})