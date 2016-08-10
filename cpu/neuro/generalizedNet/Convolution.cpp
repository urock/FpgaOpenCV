//
// Created by hokop on 8/2/16.
//

#include <cmath>
#include "Convolution.hpp"

Convolution::Convolution(int sK, int sS, Data dendrite, Data axon, string sName) :
		K(sK), S(sS), Layer(sName), preaxon(axon), bias(axon), biasGrad(axon)
{
	N = axon.N;
	M = dendrite.N;
	
	is = dendrite.M;
	os = axon.M;
	
	weight = (flt****) malloc( sizeof(flt***) * N );
	grad = (flt****) malloc( sizeof(flt***) * N );
	for(int i = 0; i < N; ++i){
		weight[i] = (flt***) malloc( sizeof(flt**) * M);
		grad[i] = (flt***) malloc( sizeof(flt**) * M);
		for(int j = 0; j < M; ++j){
			weight[i][j] = (flt**) malloc( sizeof(flt*) * K );
			grad[i][j] = (flt**) malloc( sizeof(flt*) * K );
			for (int k = 0; k < K; ++k) {
				weight[i][j][k] = (flt*) malloc( sizeof(flt) * K );
				grad[i][j][k] = (flt*) malloc( sizeof(flt) * K );
				for (int l = 0; l < K; ++l) {
					weight[i][j][k][l] = ( 2 * ( (flt) rand() / (flt) RAND_MAX ) - 1) / (flt) sqrt(K * K * M); // initial weights
				}
			}
		}
	}
	
	preaxon.initMem();
	bias.initMem();
	biasGrad.initMem();
}

bool Convolution::check() {
	if(os != axon.M || is != dendrite.M)
		throw "size error";
	if(N != axon.N || M != dendrite.N)
		throw "formats error";
	if(is != (os - (K - S)) / S || (os - (K - S)) % S != 0)
		throw "sizes of maps do not match";
	return true;
}

vector<flt*> Convolution::stretchArray(flt ****a) {
	vector<flt*> v;
	for(int i = 0; i < N; ++i)
		for (int j = 0; j < M; ++j)
			for (int k = 0; k < K; ++k)
				for (int l = 0; l < K; ++l)
					v.push_back(&a[i][j][k][l]);
	return v;
}
vector<flt*> stretchData(Data data){
	vector<flt*> v;
	for (int i = 0; i < data.N; ++i)
		for (int j = 0; j < data.M; ++j)
			for (int k = 0; k < data.M; ++k)
				v.push_back(&data.at(i, j, k));
	return v;
}

vector<flt*> Convolution::getWeights() {
	vector<flt*> a = stretchArray(weight);
	vector<flt*> b = stretchData(bias);
	a.insert(a.end(), b.begin(), b.end());
	return a;
}

vector<flt*> Convolution::getGrads() {
	vector<flt*> a = stretchArray(grad);
	vector<flt*> b = stretchData(biasGrad);
	a.insert(a.end(), b.begin(), b.end());
	return a;
}

flt f(flt x){
	return (flt) (1.0 / (1.0 + exp(-x)));
}

flt df(flt x){
	flt emx = exp(-x);
	flt opemx = 1 + emx;
	return emx / (opemx * opemx);
}

void Convolution::compute() {
	for(int row = 0; row < os; ++row)
		for (int col = 0; col < os; ++col)
			for (int map = 0; map < N; ++map)
				preaxon.at(map, row, col) = bias.at(map, row, col);
	// these cycles can be merged
	for(int row = 0; row < os; ++row)
		for (int col = 0; col < os; ++col) {
			int rS = row * S;
			int cS = col * S;
			for (int map = 0; map < N; ++map)
				for (int neuron = 0; neuron < M; ++neuron)
					for (int i = 0; i < K; ++i)
						for (int j = 0; j < K; ++j)
							preaxon.at(map, row, col) +=
									weight[map][neuron][i][j] *
									dendrite.at(neuron, rS + i, cS + j);
		}
	for(int row = 0; row < os; ++row)
		for (int col = 0; col < os; ++col)
			for (int map = 0; map < N; ++map)
				axon.at(map, row, col) = f(preaxon.at(map, row, col));
}

void Convolution::proceedError() {
	for (int map = 0; map < N; ++map)
		for (int neuron = 0; neuron < M; ++neuron)
			for (int i = 0; i < K; ++i)
				for (int j = 0; j < K; ++j)
					grad[map][neuron][i][j] = 0.0;
	for(int row = 0; row < os; ++row)
		for (int col = 0; col < os; ++col) {
			int rS = row * S;
			int cS = col * S;
			for (int map = 0; map < N; ++map) {
				flt dfS = df(preaxon.at(map, row, col));
				flt eA = errAxon.at(map, row, col);
				biasGrad.at(map, row, col) = eA * dfS;
				for (int neuron = 0; neuron < M; ++neuron)
					for (int i = 0; i < K; ++i)
						for (int j = 0; j < K; ++j) {
							grad[map][neuron][i][j] += eA * dfS * dendrite.at(neuron, rS + i, cS + j);
							errDend.at(neuron, rS + i, cS + j) += eA * dfS * weight[map][neuron][i][j];
						}
			}
		}
}