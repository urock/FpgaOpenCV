#ifndef NEURO_DESCRIPTOR
#define NEURO_DESCRIPTOR

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

#include"neuro.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

struct Descriptor
{
	//Descriptor() {};
	Descriptor( Neuro &n ) : neuro(n) {};
	~Descriptor() {};
	
	Neuro &neuro;
	
	void load( string filename );
	void save( string filename );
	
	Mat getImage();
	
};

vector<string> parseLine(string line);

#endif // NEURO_DESCRIPTOR

