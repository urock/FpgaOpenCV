//
// Created by hokop on 7/30/16.
//

#ifndef GENERALIZEDNET_GRADDESCENT_H
#define GENERALIZEDNET_GRADDESCENT_H

#include <vector>
#include "Data.hpp"

#define BATCH_SIZE 10
#define GAMMA .9f
#define EPS 1e-8f
#define SPEED 1e-3f

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
	vector<flt> realWeight;
	
	int stage;
	unsigned long weightsN;
};


#endif //GENERALIZEDNET_GRADDESCENT_H
