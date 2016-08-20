//
// Created by hokop on 7/30/16.
//

#ifndef GENERALIZEDNET_GRADDESCENT_H
#define GENERALIZEDNET_GRADDESCENT_H

#include <vector>
#include "Data.hpp"

#define BATCH_SIZE 16
#define GAMMA .9f

class GradDescent {
public:
	GradDescent() {}
	GradDescent(vector<flt*> w, vector<flt*> g);
	~GradDescent() {};
	
	void usualGD();
	void NAG();
	void adaDelta();
	void eeeRokk();
	void compute();
	
	vector<flt*> weights;
	vector<flt*> grad;
	
	// rav - running average
	vector<flt> ravGrad;
	vector<flt> ravDelta;
	vector<flt> dw;
	
	int stage;
	unsigned long weightsN;
};


#endif //GENERALIZEDNET_GRADDESCENT_H
