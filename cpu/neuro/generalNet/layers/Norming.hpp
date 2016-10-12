//
// Created by hokop on 10/12/16.
//

#ifndef GENERALIZEDNET_NORMING_HPP
#define GENERALIZEDNET_NORMING_HPP


#include "Layer.hpp"

#define DISP_EPS 1.e-8f

class Norming : public Layer
{
public:
	Norming() {}
	Norming(string sName);
	~Norming() {}
	
	virtual void setData(Data sDendrite, Data sAxon, Data sEDendrite, Data sEAxon);
	
	virtual void compute();
	virtual void proceedError();
	
	virtual vector<flt*> getWeights();
	virtual vector<flt*> getGrads();

private:
	flt mean, disp;
	flt fullNumberInversed;
	int N, M;
};


#endif //GENERALIZEDNET_NORMING_HPP
