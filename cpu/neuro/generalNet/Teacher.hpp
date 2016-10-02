//
// Created by hokop on 8/14/16.
//

#ifndef GENERALIZEDNET_TEACHER_HPP
#define GENERALIZEDNET_TEACHER_HPP

#include "layers/Network.hpp"
#include "Parser.hpp"

#define MIN_CHECKS 40

class Teacher
{
public:
	Teacher() {}
	~Teacher() {}
	
	void readWeights(string filename, Network network);
	void teach(Network &network, vector<Data> &in, vector<Data> &out, int iterations, string fileForErrors = "");
	
	void writeWeights(Network network, string filename);
};


#endif //GENERALIZEDNET_TEACHER_HPP