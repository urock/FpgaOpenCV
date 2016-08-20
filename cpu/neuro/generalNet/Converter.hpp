//
// Created by hokop on 8/16/16.
//

#ifndef GENERALIZEDNET_CONVERTER_HPP
#define GENERALIZEDNET_CONVERTER_HPP


#include <vector>
#include "Data.hpp"

class Converter
{
	Converter() {};
	~Converter() {};
	
	void loadTask(string dir, vector<string> names, vector<Data> &in, vector<Data> &out);
};


#endif //GENERALIZEDNET_CONVERTER_HPP
