//
// Created by hokop on 8/2/16.
//

#include <cmath>
#include "MaxPooling.hpp"

MaxPooling::MaxPooling(int sK, string sName) : Subsampling(sK, sName) {
	
}

void MaxPooling::setData(Data sDendrite, Data sAxon, Data sEDendrite, Data sEAxon) {
	Layer::setData(sDendrite, sAxon, sEDendrite, sEAxon);
	if(dendrite.sourcesNum != axon.sourcesNum)
		throw "max pooling layer data set error";
	choice = Data(dendrite.M, dendrite.N);
	choice.initMem();
}

MaxPooling &MaxPooling::operator=(const MaxPooling &maxPooling) {
	Subsampling::operator=(maxPooling);
	choice = maxPooling.choice;
	return *this;
}

void MaxPooling::compute() {
	for(int i = 0; i < axon.N; ++i)
		for(int j = 0; j < axon.M; ++j)
			for(int k = 0; k < axon.M; ++k) {
				int number = -1;
				flt max = -1.f;
				int jj = j * K;
				int kk = k * K;
				for(int a = 0; a < K; ++a)
					for(int b = 0; b < K; ++b) {
						flt value = dendrite.at(i, jj + a, kk + b);
						if (value > max) {
							max = value;
							number = a * K + b;
						}
					}
				axon.at(i, j, k) = max;
				choice.at(i, j, k) = number;
			}
}

void MaxPooling::proceedError() {
	for(int i = 0; i < axon.N; ++i)
		for(int j = 0; j < axon.M; ++j)
			for(int k = 0; k < axon.M; ++k) {
				int jj = j * K;
				int kk = k * K;
				int number = (int) choice.at(i, j, k);
				int a = number / K;
				int b = number % K;
				errDend.at(i, jj + a, kk + b) += errAxon.at(i, j, k);
			}
}