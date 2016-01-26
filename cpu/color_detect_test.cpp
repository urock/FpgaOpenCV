#include <iostream>
#include<fstream>
#include<string>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>

using namespace cv;
using namespace std;

// g++ color_test.cpp -lopencv_highgui -lopencv_imgproc -lopencv_core

int main()
{
	VideoCapture cap;
	cap.open("example.AVI");
	//cap.open(0);
	if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open file" << endl;
         return -1;
    }
    
	int iLowH = 2;
	int iHighH = 27;
	
	int iLowS = 200; 
	int iHighS = 255;
	
	int iLowV = 70;
	int iHighV = 255;
	
	// read settings from file
	ifstream settings("settings");
	if( settings.is_open() ){
		string line;
		stringstream ss(line);
		
		getline(settings, line);
		ss >> iLowH;
		getline(settings, line);
		ss >> iHighH;
		getline(settings, line);
		ss >> iLowS;
		getline(settings, line);
		ss >> iHighS;
		getline(settings, line);
		ss >> iLowV;
		getline(settings, line);
		ss >> iHighV;
	}
	
	Mat imgIn;
	Mat imgOut = imgIn;
	
	int iLastX = -1;
	int iLastY = -1;
	
	
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    
	VideoWriter wr;
	wr.open("output.AVI", cap.get(CV_CAP_PROP_FOURCC), cap.get(CV_CAP_PROP_FPS), S, true);
	
	if (!wr.isOpened()) {
		cout  << "Could not open the output video for write" << endl;
		return -1;
	}
	
	ofstream cordsFile;
	cordsFile.open("cords_output.txt");
	
	while(cap.read(imgIn)){
		imgOut = imgIn;
		
		Mat imgHSV;
		cvtColor(imgIn, imgHSV, COLOR_BGR2HSV);
		
		Mat imgThresholded;
		inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
		
		//morphological opening (removes small objects from the foreground)
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		
		//morphological closing (removes small holes from the foreground)
		dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
		erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
		
		//Calculate the moments of the thresholded image
		Moments oMoments = moments(imgThresholded);
		
		double dM01 = oMoments.m01;
		double dM10 = oMoments.m10;
		double dArea = oMoments.m00;
		
		if (dArea > 1000) {
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;        
			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
				//Draw a red line from the previous point to the current point
				//line(imgOut, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
				line(imgOut, Point(posX, posY), Point(0, 0), Scalar(0,0,255), 2);
			}
			iLastX = posX;
			iLastY = posY;
			//Write coordinates to file
			cordsFile << posX << ' ' << posY << '\n';
		}
		
		wr.write(imgOut);
	}
	
	cordsFile.close();
	return 0;
}
