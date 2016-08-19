//
// Created by hokop on 8/2/16.
//

#ifndef GENERALIZEDNET_SUBSAMPLING_HPP
#define GENERALIZEDNET_SUBSAMPLING_HPP


#include "Layer.hpp"

class Subsampling : public Layer
{
public:
	Subsampling(){}
	Subsampling(int sK, string sName);
	bool check();
	
	vector<flt*> getWeights();
	vector<flt*> getGrads();
	
	int K; //kernel size
};


#endif //GENERALIZEDNET_SUBSAMPLING_HPP
