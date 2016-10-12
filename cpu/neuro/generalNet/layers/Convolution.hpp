//
// Created by hokop on 8/2/16.
//

#ifndef GENERALIZEDNET_CONVOLUTION_HPP
#define GENERALIZEDNET_CONVOLUTION_HPP

#include "Layer.hpp"

class Convolution : public Layer
{
public:
	Convolution() {}
	Convolution(int sK, int sS, string sName);
	~Convolution() {}
	virtual void setData(Data sDendrite, Data sAxon, Data sEDendrite, Data sEAxon);
	
	virtual void compute();
	virtual void proceedError();
	
	virtual vector<flt*> getWeights();
	virtual vector<flt*> getGrads();
	vector<flt*> stretchArray(flt ****a);
	
	flt ****weight; // [neuron] [map] [x] [y]
	flt ****grad; // [neuron] [map] [x] [y]
	Data bias;
	Data biasGrad;
	
	Data preaxon;
	
	int K; // kernel size
	int S; // stride
	
	int N; // neurons number
	int M; // maps number
	
	int os; // output map size
	int is; // input map size
};


#endif //GENERALIZEDNET_CONVOLUTION_HPP
