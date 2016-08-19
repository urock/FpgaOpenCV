//
// Created by hokop on 7/30/16.
//

#ifndef GENERALIZEDNET_LAYER_H
#define GENERALIZEDNET_LAYER_H

#include<vector>
#include "Data.hpp"

using namespace std;

class Layer
{
public:
	Layer(){}
	Layer(string sName) : name(sName) {}
	~Layer(){}
	
	virtual Layer operator=(Layer);
	
	virtual void initData();
	
	virtual bool check();
	virtual void compute();
	virtual void proceedError();
	
	virtual vector<flt*> getWeights();
	virtual vector<flt*> getGrads();
	
	string name;
	Data dendrite;
	Data axon;
	Data errAxon;
	Data errDend;
};


#endif //GENERALIZEDNET_LAYER_H
