#!/bin/bash
g++ -std=c++11 main.cpp -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_imgcodecs
rm ../neuro/data/animals/nothing/*
rm ./output/*
./a.out 100
cp -r ./output/* ../neuro/data/animals/nothing
