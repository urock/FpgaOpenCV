//
// Created by hokop on 7/30/16.
//

#include <cmath>
#include "GradDescent.hpp"

#define EPS 1e-8f
#define SPEED .001f

GradDescent::GradDescent(vector<flt*> w, vector<flt*> g) {
	weights = w;
	grad = g;
	
	weightsN = weights.size();
	for(int i = 0; i < weightsN; ++i){
		ravGrad.push_back(EPS);
		ravDelta.push_back(EPS);
		dw.push_back(0.0);
		*grad[i] = 0.0;
	}
	
	stage = 0;
}

void GradDescent::usualGD() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = *grad[i];
		*weights[i] += SPEED * g;
		*grad[i] = 0.0f;
	}
}
void GradDescent::NAG() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = -*grad[i];
		flt d = dw[i];
		
		flt ng = SPEED * g; // for NAG, replace this
		*weights[i] += ng;
		dw[i] = GAMMA * (d + ng);
		*weights[i] += dw[i];
		
		*grad[i] = 0.0f;
	}
	// todo: check with paper
}
void GradDescent::adaDelta() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = -*grad[i];
		flt d = dw[i];
		ravDelta[i] = GAMMA * ravDelta[i] + d * d;
		ravGrad[i] = GAMMA * ravGrad[i] + g * g;
		flt ng = (flt) sqrt(ravDelta[i]) / (flt) sqrt(ravGrad[i]) * g;
		*weights[i] += ng;
		*grad[i] = 0.0f;
	}
	// todo: check with paper
}
void GradDescent::eeeRokk() {
	if(stage != 0)
		return;
	for(int i = 0; i < weightsN; ++i) {
		flt g = -*grad[i];
		flt d = dw[i];
		
		ravDelta[i] = GAMMA * ravDelta[i] + d * d;
		ravGrad[i] = GAMMA * ravGrad[i] + g * g;
		
		flt ng = (flt) sqrt(ravDelta[i]) / (flt) sqrt(ravGrad[i]) * g; // for NAG, replace this
		
		*weights[i] += ng;
		dw[i] = GAMMA * (d + ng); //for AdaDelta, replace this
		*weights[i] += dw[i]; // and remove this
		
		*grad[i] = 0.0f;
	}
}

void GradDescent::compute() {
	stage = (stage + 1) % BATCH_SIZE;
	usualGD();
	//todo: перенести сюда обнуление
}