//
// Created by hokop on 8/2/16.
//

#ifndef GENERALIZEDNET_SUBSAMPLING_HPP
#define GENERALIZEDNET_SUBSAMPLING_HPP


#include "../Layer.hpp"

class Subsampling : public Layer
{
public:
	Subsampling(){}
	Subsampling(int sK, string sName);
	//Subsampling(const Subsampling &s);
	virtual bool check();
	
	virtual Subsampling &operator=(Subsampling const &subsampling);
	
	virtual void compute();
	virtual void proceedError();
	
	virtual vector<flt*> getWeights();
	virtual vector<flt*> getGrads();
	
	int K; //kernel size
};


#endif //GENERALIZEDNET_SUBSAMPLING_HPP
