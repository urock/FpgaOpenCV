//
// Created by hokop on 8/2/16.
//

#ifndef GENERALIZEDNET_MAX_POOLING_HPP
#define GENERALIZEDNET_MAX_POOLING_HPP


#include "Subsampling.hpp"

class MaxPooling : public Subsampling
{
public:
	MaxPooling(int sK, string sName);
	virtual void compute();
	virtual void proceedError();
	virtual void setData(Data sDendrite, Data sAxon, Data sEDendrite, Data sEAxon);
	
	Data choice;
};


#endif //GENERALIZEDNET_MAX_POOLING_HPP
