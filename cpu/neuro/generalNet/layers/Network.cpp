//
// Created by hokop on 7/30/16.
//

#include <iostream>
#include "Network.hpp"

Network::Network(int sDN, int sLN) : dN(sDN), lN(sLN) {
	data = new Data[dN];
	deriv = new Data[dN];
	layer = new Layer[lN];
	seq = (int*) malloc(lN * sizeof(int));
}

Network::~Network() {}

Network &Network::operator=(Network const &network) {
	Layer::operator=(network);
	dN = network.dN;
	lN = network.lN;
	data = network.data;
	deriv = network.deriv;
	layer = network.layer;
	seq = network.seq;
	return *this;
}

Data &Network::nameToData(string name) {
	for(int i = 0; i < dN; ++i)
		if(data[i].name == name)
			return data[i];
	if(axon.name == name)
		return axon;
	if(dendrite.name == name)
		return dendrite;
	cout << "data " << name << "not found\n";
	return axon;
}

int Network::nameToLayerId(string name) {
	for(int i = 0; i < lN; ++i)
		if(layer[i].name == name)
			return i;
	cout << name << " layer id -1\n";
	return -1;
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