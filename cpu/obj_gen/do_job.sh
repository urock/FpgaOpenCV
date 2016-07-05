#!/bin/bash
g++ -std=c++11 main.cpp -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_imgcodecs
#rm -r ../neuro/data/animals/*
rm ./output/bird/* ./output/dog/* ./output/human/* ./output/tree/*
./a.out 100 human bird tree dog
cp -r ./output/* ../neuro/data/animals/
