//
// Created by hokop on 8/2/16.
//

#include "Subsampling.hpp"

Subsampling::Subsampling(int sK, string sName) : Layer(sName), K(sK) {}

//Subsampling::Subsampling(const Subsampling &s) :  Subsampling(s.K, s.name) {
//	//todo: normal constructor
//}

Subsampling &Subsampling::operator=(Subsampling const &subsampling) {
	Layer::operator=(subsampling);
	K = subsampling.K;
	return *this;
}

bool Subsampling::check() {
	return dendrite.M % K == 0 && dendrite.M / K == axon.M && dendrite.N == axon.N;
}

void Subsampling::compute() {
	
}

void Subsampling::proceedError() {
	
}

// no weights and no grads in subsampling layer
vector<flt*> Subsampling::getWeights() {
	vector<flt*> v;
	return v;
}

vector<flt*> Subsampling::getGrads() {
	vector<flt*> v;
	return v;
}