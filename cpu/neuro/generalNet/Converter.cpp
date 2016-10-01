//
// Created by hokop on 8/16/16.
//

#include "Converter.hpp"

#include<fstream>
#include <dirent.h>
#include <iostream>

#include "opencv2/highgui/highgui.hpp"

using namespace cv;

int getDir(string dir, vector<string> &files)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp  = opendir(dir.c_str())) == NULL) {
		cout << "Error(" << errno << ") opening " << dir << endl;
		return errno;
	}
	
	while ((dirp = readdir(dp)) != NULL) {
		files.push_back(string(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

Data matToData(Mat img) {
	Data data(img.rows, img.channels());
	data.initMem();
	for(int c = 0; c < img.channels(); ++c)
		for(int i = 0; i < img.rows; ++i)
			for (int j = 0; j < img.rows; ++j)
				data.at(c, i, j) = (flt) ((Scalar)img.at<flt>(i, j))[c];
	return data;
	//todo: check adequacy
}

Data indexToData(int index, int size) {
	Data data(1, size);
	data.initMem();
	for(int i = 0; i < size; ++i)
		data.at(i, 0, 0) = (i == index)? 1.0f : 0.0f;
	return data;
	//todo: check adequacy
}

void Converter::loadTask(string dir, vector<string> names, vector<Data> &in, vector<Data> &out) {
	int species = (int) names.size();
	for(int i = 0; i < species; ++i) {
		string folder = dir + names[i] + string("/");
		vector<string> files;
		getDir(folder, files);
		Data dataOut = indexToData(i, species);
		for(int k = 0; k < files.size(); ++k) {
			if(files[k] == "." or files[k] == "..")
				continue;
			string name = folder + files[k];
			Mat img = imread(name, CV_LOAD_IMAGE_GRAYSCALE);
			Data dataIn = matToData(img);
			in.push_back(dataIn);
			out.push_back(dataOut);
		}
	}
}
