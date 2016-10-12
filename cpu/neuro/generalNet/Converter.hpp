//
// Created by hokop on 8/16/16.
//

#ifndef GENERALIZEDNET_CONVERTER_HPP
#define GENERALIZEDNET_CONVERTER_HPP


#include <vector>
#include "Data.hpp"
#include<fstream>
#include <dirent.h>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class Converter
{
public:
	Converter() {};
	~Converter() {};
	
	void loadTask_Type1(string dir, vector<string> names, vector<Data> &in, vector<Data> &out);
};

Data matToData(Mat &img);
Data indexToData(int index, int size);


#endif //GENERALIZEDNET_CONVERTER_HPP
