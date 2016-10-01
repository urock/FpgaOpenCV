//
// Created by hokop on 7/30/16.
//

#ifndef GENERALIZEDNET_NETWORK_H
#define GENERALIZEDNET_NETWORK_H


#include "../Data.hpp"
#include "../Layer.hpp"

class Network : public Layer
{
public:
	Network() : dN(0), lN(0) {}
	Network(int sDN, int sLN);
	~Network();
	
	Network &operator=(Network const &network);
	
	Data &nameToData(string name);
	int nameToLayerId(string name);
	
	bool check();
	void compute();
	void proceedError();
	
	vector<flt*> getWeights();
	vector<flt*> getGrads();
	
	int dN, lN; // number of datas and layers
	
	Data *data;
	Data *deriv;
	
	Layer *layer;
	
	int *seq;
};


#endif //GENERALIZEDNET_NETWORK_H
