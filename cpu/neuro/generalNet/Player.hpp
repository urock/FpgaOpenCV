//
// Created by hokop on 10/9/16.
//

#ifndef GENERALIZEDNET_PLAYER_HPP
#define GENERALIZEDNET_PLAYER_HPP

#include "opencv2/highgui/highgui.hpp"
#include <opencv2/imgproc.hpp>
#include "Data.hpp"
#include "layers/Network.hpp"
#include "Converter.hpp"
#include "Teacher.hpp"

using namespace cv;
using namespace std;

class Player
{
public:
	Player() {};
	~Player() {};
	
	void getObjects(Mat const &img, Network *network, vector<Data> &theory, vector<int> &ids, vector<int> &x, vector<int> &y, vector<int> &size);
	Mat highlightObjects(Mat const &img, Network *network, vector<Data> &theory, vector<string> &names);
	void processCamera(Network *network, vector<Data> &theory, vector<string> &names);
	void processVideeo(Network *network, vector<Data> &theory, vector<string> &names, string inputName, string outputName);
};

flt error(Data &real, Data &theor);

#endif //GENERALIZEDNET_PLAYER_HPP
