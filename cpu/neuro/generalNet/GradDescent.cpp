//
// Created by hokop on 7/30/16.
//

#include <cmath>
#include "GradDescent.hpp"

GradDescent::GradDescent(vector<flt*> w, vector<flt*> g) {
	weights = w;
	grad = g;
	
	weightsN = weights.size();
	for(int i = 0; i < weightsN; ++i){
		ravGrad.push_back(EPS);
		ravDelta.push_back(EPS);
		dw.push_back(0.0);
		*grad[i] = 0.0;
		realWeight.push_back(*weights[i]);
	}
	
	stage = 0;
}

void GradDescent::usualGD() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = -*grad[i];
		*weights[i] += SPEED * g;
		*grad[i] = 0.0f;
	}
}
void GradDescent::NAG() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = -*grad[i];
		flt oldSpd = dw[i];
		
		flt ng = SPEED * g;
		dw[i] = GAMMA * oldSpd + ng;
		realWeight[i] += dw[i];
		
		*weights[i] = realWeight[i] + GAMMA * oldSpd;
		
		*grad[i] = 0.0f;
	}
}
void GradDescent::adaDelta() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = -*grad[i];
		
		ravGrad[i] = GAMMA * ravGrad[i] + g * g * (1.f - GAMMA);
		flt ng = (flt) sqrt(ravDelta[i] + EPS) / (flt) sqrt(ravGrad[i] + EPS) * g;
		ravDelta[i] = GAMMA * ravDelta[i] + ng * ng * (1.f - GAMMA);
		
		*weights[i] += ng;
		
		*grad[i] = 0.0f;
	}
}
void GradDescent::eeeRokk() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = -*grad[i];
		flt oldSpd = dw[i];
		
		ravGrad[i] = GAMMA * ravGrad[i] + g * g * (1.f - GAMMA);
		flt ng = ((flt) sqrt(ravDelta[i] + EPS) / (flt) sqrt(ravGrad[i] + EPS)) * g;
		dw[i] = GAMMA * oldSpd + ng + SPEED * g;
		ravDelta[i] = GAMMA * ravDelta[i] + ng * ng * (1.f - GAMMA);
		
		realWeight[i] = realWeight[i] + dw[i];
		
		*weights[i] = realWeight[i] + GAMMA * oldSpd;
		
		*grad[i] = 0.0f;
	}
}

void GradDescent::compute() {
	stage = (stage + 1) % BATCH_SIZE;
	adaDelta();
}