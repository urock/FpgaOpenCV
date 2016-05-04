#!/bin/bash

g++ -std=c++11 neuro.hpp loader.hpp
g++ -o neuro -std=c++11 main.cpp neuro.cpp loader.cpp
rm *.hpp.gch
