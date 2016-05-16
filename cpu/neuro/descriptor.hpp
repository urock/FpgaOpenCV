#ifndef NEURO_DESCRIPTOR
#define NEURO_DESCRIPTOR

#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

#include"neuro.hpp"
#include"teacher.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>

using namespace std;
using namespace cv;

struct Descriptor
{
	Descriptor( Neuro &n ) : neuro(n) {};
	~Descriptor() {};
	
	Neuro &neuro;
	
	void load( string filename );
	void save( string filename );
	
	Mat getImage();
	Mat getLayerImage(int L, vec what);
	
	void pseudoTeachLayer( const vec &inputVal, int outputSz, const vec &deriv, flt **weight, vec &nextDeriv );
};

vector<string> parseLine(string line);
vec imgToVec( Mat &img );
Mat vecToImg( vec &v );

vector< vector<vec> > loadClassificationTask( string dir, vector<string> names );
vector<vec> generateTheory( int size );

#endif // NEURO_DESCRIPTOR

