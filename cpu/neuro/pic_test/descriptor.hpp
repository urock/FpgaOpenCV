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

#include"mlp.hpp"

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include "opencv2/videoio.hpp"

using namespace std;
using namespace cv;

typedef vector<flt> vec;

struct Descriptor
{
	//Descriptor() {};
	Descriptor( MLP &n ) : mlp(n) {};
	~Descriptor() {};
	
	MLP &mlp;
	
	void load( string filename );
	void save( string filename );
	
	Mat getImage();
	Mat getLayerImage(int L, vec what, vec white = vec(0));
	
	Mat preprocessImage(Mat image, float alpha = 4);
	Mat processImage(Mat img, int width, vector<vec> theory, vector<string> names,
				int mult = 1, int step = 10, flt tolerance = .01);
	void processVideo(string inputName, string outputName, vector<vec> theory, vector<string> names);
	
	void pseudoTeachLayer( const vec &inputVal, int outputSz, const vec &deriv, flt **weight, vec &nextDeriv );
};

vector<string> parseLine(string line);
vec imgToVec( Mat &img, int mult = 1 );
Mat vecToImg( vec &v );

vector< vector<vec> > loadClassificationTask( string dir, vector<string> names );
vector<vec> generateTheory( int size );

#endif // NEURO_DESCRIPTOR

