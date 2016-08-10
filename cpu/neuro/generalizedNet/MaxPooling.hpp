//
// Created by hokop on 8/2/16.
//

#ifndef GENERALIZEDNET_MAX_POOLING_HPP
#define GENERALIZEDNET_MAX_POOLING_HPP


#include "Subsampling.hpp"

class MaxPooling : public Subsampling
{
	MaxPooling(int sK, string sName);
	void compute();
	void proceedError();
	
	Data choice;
};


#endif //GENERALIZEDNET_MAX_POOLING_HPP
