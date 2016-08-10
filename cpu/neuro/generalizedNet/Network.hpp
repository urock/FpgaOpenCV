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
	Network() {}
	Network(int sDN, int sLN);
	
	int nameToId(string name);
	void connect(string name1, string name2);
	
	bool check();
	void compute();
	void proceedError();
	
	int dN, lN; // number of datas and layers
	
	Data *data;
	Data *deriv;
	
	Layer *layer;
	
	int *seq;
};


#endif //GENERALIZEDNET_NETWORK_H
