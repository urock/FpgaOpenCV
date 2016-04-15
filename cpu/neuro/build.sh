#!/bin/bash

g++  -std=c++0x neuro.hpp descriptor.hpp
g++  -std=c++0x main.cpp neuro.cpp descriptor.cpp -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_imgcodecs
rm *.hpp.gch
