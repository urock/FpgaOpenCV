//
// Created by hokop on 8/12/16.
//

#include "Layer.hpp"

void Layer::initData() {
	axon.initMem();
	errDend.initMem();
}

Layer Layer::operator=(Layer layer) {
	name = layer.name;
	axon = layer.axon;
	dendrite = layer.dendrite;
	errAxon = layer.errAxon;
	errDend = layer.errDend;
	return *this;
}