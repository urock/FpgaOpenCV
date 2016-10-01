//
// Created by hokop on 8/12/16.
//

#include "Layer.hpp"

bool Layer::check() {}
void Layer::compute() {}
void Layer::proceedError() {}

void Layer::setData(Data sDendrite, Data sAxon) {
	dendrite = sDendrite;
	axon = sAxon;
	
	errDend = dendrite;
	errDend.initMem();
	errAxon = axon;
	errAxon.initMem();
}

vector<flt*> Layer::getWeights() {
	return vector<flt*>();
}
vector<flt*> Layer::getGrads() {return vector<flt*>(); }

//Layer Layer::operator=(Layer layer) {
//	name = layer.name;
//	axon = layer.axon;
//	dendrite = layer.dendrite;
//	errAxon = layer.errAxon;
//	errDend = layer.errDend;
//	return *this;
//}