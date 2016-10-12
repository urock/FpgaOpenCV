//
// Created by hokop on 10/12/16.
//

#include "Norming.hpp"

Norming::Norming(string sName) : Layer(sName) {
	
}

void Norming::setData(Data sDendrite, Data sAxon, Data sEDendrite, Data sEAxon) {
	if(sDendrite.N != sAxon.N || sDendrite.M != sAxon.M)
		throw "Norming layer: data type mismatch";
	
	Layer::setData(sDendrite, sAxon, sEDendrite, sEAxon);
	N = dendrite.N;
	M = dendrite.M;
	fullNumberInversed = 1.f / (flt) (N * M * M);
}

void Norming::compute() {
	flt sqrSum = 0.f, sum = 0.f;
	for(int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			for (int k = 0; k < M; ++k) {
				flt val = dendrite.at(i, j, k);
				sqrSum = sqrSum + val * val;
				sum = sum + val;
			}
	mean = sum * fullNumberInversed;
	disp = sqrSum * fullNumberInversed - mean * mean;
	if(disp < DISP_EPS)
		disp = 1.f;
	flt dm1 = 1.f / disp;
	for(int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			for (int k = 0; k < M; ++k)
				axon.at(i, j, k) = (dendrite.at(i, j, k) - mean) * dm1;
}

void Norming::proceedError() {
	flt dm1 = 1.f / disp;
	for(int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			for (int k = 0; k < M; ++k)
				errDend.at(i, j, k) = dm1 * errAxon.at(i, j, k); // dE/dD = dE/dA * dA/dD = dE/dA * dm1
}

vector<flt *> Norming::getWeights() {
	return Layer::getWeights();
}

vector<flt *> Norming::getGrads() {
	return Layer::getGrads();
}
