//
// Created by hokop on 10/9/16.
//

#include "Player.hpp"

void Player::getObjects(Mat const &img, Network *network, vector<Data> &theory, vector<int> &ids, vector<int> &x, vector<int> &y, vector<int> &size) {
	int width = network->dendrite.M;
	for(int w = width * 8; w < width * 16; w *= 2) {
		int stride = w / 4 + 1;
		for (int xStart = 0; xStart + w < img.cols; xStart += stride) {
			for (int yStart = 0; yStart + w < img.rows; yStart += stride) {
				Rect rect(xStart, yStart, w, w);
				Mat part = img(rect).clone();
				resize(part, part, Size(width, width));
				Data data = matToData(part);
				network->dendrite.copyFrom(data);
				network->compute();
				int id = -1;
				flt min = 8.f;
				for (int i = 0; i < theory.size(); ++i) {
					flt err = error(network->axon, theory[i]);
					if (err < min) {
						min = err;
						id = i;
					}
				}
				if (id != 1) {
					ids.push_back(id);
					x.push_back(xStart);
					y.push_back(yStart);
					size.push_back(w);
				}
				data.clearMem();
			}
		}
	}
}

Mat Player::highlightObjects(Mat const &img, Network *network, vector<Data> &theory, vector<string> &names) {
	Mat result;
	cvtColor(img, result, CV_GRAY2BGR);
	vector<int> ids, x, y, size;
	getObjects(img, network, theory, ids, x, y, size);
	
	for(int i = 0; i < ids.size(); ++i) {
		Rect rect(x[i], y[i], size[i], size[i]);
		rectangle( result, rect, 255, 1 );
		putText(result, names[ids[i]], Point(x[i], y[i]), FONT_HERSHEY_SIMPLEX, .5, 255);
	}
	
	return result;
}

void Player::processCamera(Network *network, vector<Data> &theory, vector<string> &names) {
	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened())  // check if we succeeded
		throw "could not open camera";
	
	Mat result;
	namedWindow("result",1);
	for(;;)
	{
		Mat frame;
		cap >> frame; // get a new frame from camera
		cvtColor(frame, result, CV_BGR2GRAY);
		result = highlightObjects(result, network, theory, names);
		imshow("result", result);
		if(waitKey(30) >= 0) break;
	}
}

void
Player::processVideeo(Network *network, vector<Data> &theory, vector<string> &names, string inputName, string outputName) {
	VideoCapture cap(inputName);
	if( !cap.isOpened() ) {
		cout << "Couldn't open the input video\n";
		return;
	}
	
	Size S = Size((int) cap.get(CV_CAP_PROP_FRAME_WIDTH),    // Acquire input size
				  (int) cap.get(CV_CAP_PROP_FRAME_HEIGHT));
	VideoWriter wr;
	double fps = cap.get(CV_CAP_PROP_FPS);
	fps = 15; // COSTyL
	wr.open(outputName, cap.get(CV_CAP_PROP_FOURCC), fps, S, true);
	if (!wr.isOpened()) {
		cout  << "Could not open the output video for write" << endl;
		return;
	}
	
	Mat img;
	int i = 0;
	while ( cap.read(img) ) {
		if (img.empty())
			continue;
		
		if( i % 100 == 0 )
			cout << i << endl;
		++i;
		
		cvtColor(img, img, CV_BGR2GRAY);
		img = highlightObjects(img, network, theory, names);
		
		wr.write(img);
	}
}



