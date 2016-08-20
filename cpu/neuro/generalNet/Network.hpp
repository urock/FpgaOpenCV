//
// Created by hokop on 7/30/16.
//

#ifndef GENERALIZEDNET_NETWORK_H
#define GENERALIZEDNET_NETWORK_H


#include "Data.hpp"
#include "Layer.hpp"

class Network : public Layer
{
public:
	Network() : dN(0), lN(0) {}
	Network(int sDN, int sLN);
	~Network();
	
	Network operator=(Network);
	
	void initData();
	
	int nameToDataId(string name);
	int nameToLayerId(string name);
	void connectAxon(string dName, string lName); // data to layer
	void connectDendrite(string dName, string lName);
	
	bool check();
	void compute();
	void proceedError();
	
	vector<flt*> getWeights();
	vector<flt*> getGrads();
	
	virtual Layer operator=(Layer layer) override;
	
	int dN, lN; // number of datas and layers
	
	Data *data;
	Data *deriv;
	
	Layer *layer;
	
	int *seq;
};


#endif //GENERALIZEDNET_NETWORK_H
