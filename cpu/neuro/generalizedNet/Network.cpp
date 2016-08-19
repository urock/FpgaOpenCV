//
// Created by hokop on 7/30/16.
//

#include "Network.hpp"

Network::Network(int sDN, int sLN) : dN(sDN), lN(sLN) {
	data = (Data*) malloc(dN * sizeof(Data));
	layer = (Layer*) malloc(lN * sizeof(Layer));
	seq = (int*) malloc(lN * sizeof(int));
}

Network::~Network() {}

void Network::initData() {
	for(int i = 0; i < lN; ++i)
		layer[i].initData();
}

Network Network::operator=(Network network) {
	Layer::operator=(network);
	dN = network.dN;
	lN = network.lN;
	data = network.data;
	deriv = network.deriv;
	layer = network.layer;
	seq = network.seq;
	return *this;
}

int Network::nameToDataId(string name) {
	for(int i = 0; i < dN; ++i)
		if(data[i].name == name)
			return i;
	return -1;
}

int Network::nameToLayerId(string name) {
	for(int i = 0; i < lN; ++i)
		if(layer[i].name == name)
			return i;
	return -1;
}

void Network::connectAxon(string dName, string lName) {
	int di = nameToDataId(dName);
	int li = nameToLayerId(lName);
	layer[li].axon = data[di];
	layer[li].errAxon = deriv[di];
}

void Network::connectDendrite(string dName, string lName) {
	int di = nameToDataId(dName);
	int li = nameToLayerId(lName);
	layer[li].dendrite = data[di];
	layer[li].errDend = deriv[di];
}

bool Network::check() {
	bool res = true;
	for(int i = 0; i < lN; ++i)
		res = res && layer[i].check();
	return res;
}

void Network::compute() {
	for(int i = 0; i < lN; ++i)
		layer[seq[i]].compute();
}
void Network::proceedError() {
	for(int i = lN - 1; i != 0; --i)
		layer[seq[i]].proceedError();
}

vector<flt*> Network::getWeights() {
	vector<flt*> a;
	for (int i = 0; i < lN; ++i) {
		vector<flt*> b = layer[i].getWeights();
		a.insert(a.end(), b.begin(), b.end());
	}
	return a;
}

vector<flt*> Network::getGrads() {
	vector<flt*> a;
	for (int i = 0; i < lN; ++i) {
		vector<flt*> b = layer[i].getGrads();
		a.insert(a.end(), b.begin(), b.end());
	}
	return a;
}