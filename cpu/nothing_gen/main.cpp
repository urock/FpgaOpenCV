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

int sz = 32;
int maxThick = 16;
int linesMaxN = 17;
int minLinesN = 1;
float noise1Level = .8;
float noise2Level = .2;

float alpha1 = .5, alpha2 = 2;
int beta1 = -16, beta2 = 16;

Mat variant();

int main( int argc, char* argv[] ){
	srand( time(0) );
	
	int N = atoi(argv[1]);
	
	string name = "nothing";
	for(int j = 0; j < N; ++j) {
		string oname = string("output/") + name + to_string(j) + string(".png");
		Mat res = variant();
		imwrite(oname.c_str(), res);
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

Mat variant(){
	Mat res( sz, sz, CV_8UC1, Scalar::all(255) );
	
	int light = rand() % 4;
	
	int linesN = rand() % (linesMaxN - minLinesN + 1) + minLinesN;
	if(rand() % 50 == 0) {
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
		
		int thick = rand() % (maxThick + 1);
		if(thick >= maxThick / 2)
			thick = rand() % (maxThick + 1);
		
		line(res, Point(x1, y1), Point(x2, y2), Scalar( rand() % 256 ), thick );
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
	
	// invert colors
	if(rand() % 2 == 0)
		bitwise_not ( res, res );
	
	return res;
}












