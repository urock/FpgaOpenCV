//
// Created by hokop on 8/14/16.
//

#include <fstream>
#include "Teacher.hpp"
#include "GradDescent.hpp"

void Teacher::readWeights(string filename, Network network) {
	Line line = Block(filename)[0];
	vector<flt*> weights = network.getWeights();
	for(int i = 0; i < weights.size(); ++i)
		*weights[i] = atof(line[i].c_str());
}

void Teacher::writeWeights(Network network, string filename) {
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

void countErrDeriv(Data &real, Data &theor, Data &deriv) {
	deriv.resetMem();
	for (int i = 0; i < real.N; ++i)
		for (int j = 0; j < real.M; ++j)
			for (int k = 0; k < real.M; ++k)
				deriv.at(i, j, k) = real.at(i, j, k) - theor.at(i, j, k);
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
	for(int i = 0; i < bigIters; ++i) {
		if(f.is_open()) {
			network.dendrite.copyFrom(in[crossId]);
			network.compute();
			f << error(network.axon, out[crossId]) << endl;
		}
		for(int j = 0; j < size; ++j) {
			if(j == crossId)
				continue;
			network.dendrite.copyFrom(in[j]);
			network.compute();
			countErrDeriv(network.axon, out[i], network.errAxon);
			network.proceedError();
			gradDescent.compute();
		}
		crossId = (crossId + 1) % size;
	}
}