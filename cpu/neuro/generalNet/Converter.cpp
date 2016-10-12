//
// Created by hokop on 8/16/16.
//

#include "Converter.hpp"

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

Data matToData(Mat &img) {
	Data data(img.rows, img.channels());
	data.initMem();
	for(int c = 0; c < img.channels(); ++c)
		for(int i = 0; i < img.cols; ++i)
			for (int j = 0; j < img.rows; ++j) {
				flt a = (flt)img.at<uchar>(i, j) / 255.0f;
				data.at(c, i, j) = a;
			}
	return data;
}

Data indexToData(int index, int size) {
	Data data(1, size);
	data.initMem();
	for(int i = 0; i < size; ++i)
		data.at(i, 0, 0) = (i == index)? 1.0f : -1.0f;
	return data;
}

// type 1 task - when folders with names "names" contain images and theory is generated just as delta-simbol
void Converter::loadTask_Type1(string dir, vector<string> names, vector<Data> &in, vector<Data> &out) {
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
	for(int i = 0; i < in.size() * 2; ++i) {
		int position = rand() % (int)in.size();
		int nextPosition = rand() % (int)in.size();
		iter_swap(in.begin() + position, in.begin() + nextPosition);
		iter_swap(out.begin() + position, out.begin() + nextPosition);
	}
}
