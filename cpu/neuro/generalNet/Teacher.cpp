//
// Created by hokop on 8/14/16.
//

#include <fstream>
#include "Teacher.hpp"
#include "GradDescent.hpp"

void Teacher::readWeights(string filename, Network &network) {
	ifstream f(filename.c_str());
	string str;
	getline(f, str);
	Line line;
	line = str;
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
		int start = i * size % (int)in.size();
		int end = (start + size) % (int)in.size();
		for(int j = start; j < end; j = (j + 1) % (int)in.size()) {
			if(j == crossId)
				continue;
			network.dendrite.copyFrom(in[j]);
			network.compute();
			countErrDeriv(network.axon, out[j], network.errAxon);
			network.proceedError();
			gradDescent.compute();
		}
		if(f.is_open()) {
			network.dendrite.copyFrom(in[crossId]);
			network.compute();
			f << error(network.axon, out[crossId]) << '\t';
//			f << '\t' << out[crossId].at(0,0,0) << '\t' << out[crossId].at(1,0,0) << '\t' <<
//					network.axon.at(0,0,0) << '\t' << network.axon.at(1,0,0) << '\t' << endl;
//			f << out[crossId].at(0,0,0) - network.axon.at(0,0,0) << '\t'
//					<< out[crossId].at(1,0,0) - network.axon.at(1,0,0) << endl;
			f << network.axon.at(0,0,0) << '\t'
			  << network.axon.at(1,0,0) << endl;
		}
		crossId = (crossId + 1) % (int)in.size();
	}
}