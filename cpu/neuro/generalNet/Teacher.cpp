//
// Created by hokop on 8/14/16.
//

#include <fstream>
#include <cmath>
#include "Teacher.hpp"
#include "GradDescent.hpp"

void readWeights(string filename, Network &network) {
	ifstream f(filename.c_str());
	string str;
	getline(f, str);
	Line line;
	line = str;
	vector<flt*> weights = network.getWeights();
	for(int i = 0; i < weights.size(); ++i)
		*weights[i] = atof(line[i].c_str());
}

void writeWeights(Network network, string filename) {
	ofstream f(filename.c_str());
	vector<flt*> weights = network.getWeights();
	for(int i = 0; i < weights.size(); ++i)
		f << *weights[i] << " ";
	f.close();
}

flt error(Data &real, Data &theor) {
	flt sum = 0;
	for (int i = 0; i < real.N; ++i)
		for (int j = 0; j < real.M; ++j)
			for (int k = 0; k < real.M; ++k) {
				flt t = real.at(i, j, k) - theor.at(i, j, k);
				sum += t * t;
			}
	return sum;
}

void countErrDeriv(Data &real, Data &theor, Data &deriv, flt threshold = 0.f) {
	for (int i = 0; i < real.N; ++i)
		for (int j = 0; j < real.M; ++j)
			for (int k = 0; k < real.M; ++k) {
				flt d = real.at(i, j, k) - theor.at(i, j, k);
				deriv.at(i, j, k) = (d > threshold)? d - threshold :
									(d < -threshold)? d + threshold : 0.f;
			}
}

void Teacher::teach(Network &network, vector<Data> &in, vector<Data> &out, int iterations, string fileForErrors) {
	if(in.size() != out.size())
		throw "Error: input and output sizes do not match";
	GradDescent gradDescent(network.getWeights(), network.getGrads());
	int crossId = 0;
	int size = (int) in.size();
	int bigIters = iterations / size;
	if(bigIters < MIN_CHECKS) {
		bigIters = MIN_CHECKS;
		size = iterations / bigIters;
	}
	
	ofstream f(fileForErrors.c_str());
	flt runningError = 0.f;
	flt smoothError = 0.f;
	flt gamma = .9f;
	flt norm = 1.0f / (1.0f - gamma);
	
	for(int i = 0; i < bigIters; ++i) {
		int start = i * size % (int)in.size();
		int end = (start + size) % (int)in.size();
		for(int j = start; j < end; j = (j + 1) % (int)in.size()) {
			if(j == crossId)
				continue;
			network.dendrite.copyFrom(in[j]);
			network.compute();
//			countErrDeriv(network.axon, out[j], network.errAxon, .5f + .5f * sin(3.14f * i / 100.f));
			countErrDeriv(network.axon, out[j], network.errAxon);
			if(error(network.axon, out[j]) > ACCEPTABLE_ERR) {
				network.proceedError();
				gradDescent.compute();
			}
		}
		if(f.is_open()) {
			network.dendrite.copyFrom(in[crossId]);
			network.compute();
			flt e = error(network.axon, out[crossId]);
			if(i == 0)
				runningError = smoothError = e;
			runningError = runningError * gamma + e / norm;
			smoothError = smoothError * gamma + runningError / norm;
			f << e << '\t' << smoothError << '\t';
			f << network.axon.at(0,0,0) << endl;
		}
		crossId = (crossId + 1) % (int)in.size();
	}
}