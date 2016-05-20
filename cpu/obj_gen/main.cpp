#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<vector>

#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>

using namespace cv;
using namespace std;

// g++ main.cpp -lopencv_highgui -lopencv_imgproc -lopencv_core -lopencv_imgcodecs
// ./a.out 2000 human bird tree dog nothing1 nothing2 nothing3 nothing4 nothing5 nothing6 nothing7 nothing8 nothing9 nothing10

float rot = 45.;
float resizeAmp = .6;
float squeezeAmp = .2;
float noise1Level = .8;
float noise2Level = .4;
bool allowFlip = false;
int sz = 32;
int rad = 30;

int maxThick = 4;
int linesMaxN = 2;
int minLinesN = 0;

float alpha1 = .9, alpha2 = 1.;
int beta1 = -4, beta2 = 4;

Mat variant(Mat obj);

int main( int argc, char* argv[] ){
	srand( time(0) );
	
	int N = atoi(argv[1]);
	int pics = argc - 2;
	
	for(int i = 0; i < pics; ++i) {
		string name = argv[i+2];
		string iname = string("input/") + name + string(".png");
		Mat obj = imread(iname.c_str(), CV_LOAD_IMAGE_GRAYSCALE );
		for(int j = 0; j < N; ++j) {
			string oname = string("output/") + name + string("/") + name + to_string(j) + string(".png");
			Mat res = variant(obj);
			imwrite(oname.c_str(), res);
		}
	}
	
	return 0;
}

Mat change_CB(Mat image, float alpha, int beta) {
	Mat new_image = Mat::zeros( image.size(), image.type() );
	
	/// Do the operation new_image(i,j) = alpha*image(i,j) + beta
	for( int y = 0; y < image.rows; y++ ) {
		for( int x = 0; x < image.cols; x++ ) {
			new_image.at<uchar>(y,x) = saturate_cast<uchar>( alpha*( image.at<uchar>(y,x) ) + beta );
		}
	}
	return new_image;
}

Mat variant(Mat obj){
	double resiz = (float) rand() / (float) RAND_MAX * resizeAmp;
	double scaleX = 1.0 - resiz - squeezeAmp * (float) rand() / (float) RAND_MAX;
	double scaleY = 1.0 - resiz - squeezeAmp * (float) rand() / (float) RAND_MAX;
	cv::resize(obj, obj, Size(rad*scaleX, rad*scaleY) );
	
	/// Compute a rotation matrix with respect to the center of the image
	Point center = Point( obj.cols/2, obj.rows/2 );
	double angle = ( (float) rand() / (float) RAND_MAX * 2.0 - 1.0 ) * rot;
	
	// Get the rotation matrix with the specifications above
	Mat rot_mat = getRotationMatrix2D( center, angle, 1.0 ); //scale = 1.0
	
	// Rotate the warped image
	warpAffine( obj, obj, rot_mat, obj.size(), INTER_LINEAR, BORDER_CONSTANT, Scalar::all(255) );
	
	if(allowFlip)
		if(rand() % 2 == 0)
			flip(obj, obj, 1);
	
	Mat res( sz, sz, CV_8UC1, Scalar::all(255) );
	
	/// draw one mat on another
	int x = rand() % (res.cols - obj.cols);
	int y = rand() % (res.rows - obj.rows);
	
	obj.copyTo(res.rowRange(y, y + obj.rows).colRange(x, x + obj.cols));
	
	// add random lines
	int light = rand() % 4;
	int linesN = rand() % (linesMaxN - minLinesN + 1) + minLinesN;
	if(rand() % 6 == 0) {
		linesN = 0;
		int x1 = rand() % res.cols;
		int y1 = rand() % res.rows;
		circle(res, Point(x1, y1), 0, Scalar(0));
	}
	for(int i = 0; i < linesN; ++i) {
		int x1 = rand() % res.cols * 3 - res.cols;
		int y1 = rand() % res.rows * 3 - res.rows;
		int x2 = rand() % res.cols * 3 - res.cols;
		int y2 = rand() % res.rows * 3 - res.rows;
		
		if( fabs((x1 + x2) - res.cols) < maxThick * 4 && fabs((y1 + y2) - res.rows) < maxThick * 4 )
			continue;
		
		line(res, Point(x1, y1), Point(x2, y2), Scalar( rand() % 256 ), rand() % (maxThick + 1) );
	}
	
	// add noise
	Mat noise1 = res.clone();
	Mat noise2 = res.clone();
	float noise1L = noise1Level * ( rand() % 4 ) / 4.;
	float noise2L = noise2Level * ( rand() % 4 ) / 4.;
	randn(noise1, 0, noise1L * 255);
	randn(noise2, 0, noise2L * 255);
	res += noise1;
	res -= noise2;
	normalize(res, res, 0, 255, CV_MINMAX, CV_8UC1);
	
	// change conrast and brightness
	float alpha = alpha1 + (float) rand() / (float) RAND_MAX * (alpha2 - alpha1);
	int beta = beta1 + rand() % (beta2 - beta1 + 1);
	res = change_CB(res, alpha, beta);
	
	return res;
}












