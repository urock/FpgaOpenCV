//
// Created by hokop on 8/2/16.
//

#ifndef GENERALIZEDNET_CONVOLUTION_HPP
#define GENERALIZEDNET_CONVOLUTION_HPP

#include "../Layer.hpp"

class Convolution : public Layer
{
public:
	Convolution() {}
	Convolution(int sK, int sS, string sName);
	~Convolution() {}
	virtual void setData(Data dendrite, Data axon, Data sEDendrite, Data sEAxon);
	virtual bool check();
	
	Convolution &operator=(Convolution const &);
	
	virtual void compute();
	virtual void proceedError();
	
	vector<flt*> stretchArray(flt ****a);
	virtual vector<flt*> getWeights();
	virtual vector<flt*> getGrads();
	
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
