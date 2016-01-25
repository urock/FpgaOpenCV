#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;
using namespace std;

// компиляция:
// g++ color_test.cpp -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_core

int main()
{
	VideoCapture cap;
	cap.open("example.avi");
	//cap.open(0);
	if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open file" << endl;
         return -1;
    }
    
	int iLowH = 4;
	int iHighH = 27;
	
	int iLowS = 113; 
	int iHighS = 195;
	
	int iLowV = 83;
	int iHighV = 220;
	
	Mat imgIn;
	Mat imgOut;
	
	int iLastX = -1;
	int iLastY = -1;
	
	
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
                  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    
	VideoWriter wr;
	wr.open("output/ball.avi", -1, 30, S, true);
	
	if (!wr.isOpened()) {
		cout  << "Could not open the output video for write" << endl;
		return -1;
	}
	
	while(cap.read(imgIn)){
		Mat imgThresholded;
		inRange(imgIn, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded);
		
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
		
		if (dArea > 10000) {
			//calculate the position of the ball
			int posX = dM10 / dArea;
			int posY = dM01 / dArea;        
			if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
			{
			//Draw a red line from the previous point to the current point
			line(imgOut, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
			}
			iLastX = posX;
			iLastY = posY;
		}
		
		wr.write(imgOut);
		
		cout << "i";
	}
	
	return 0;
}
