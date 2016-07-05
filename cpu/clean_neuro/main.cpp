#include<iostream>
#include<time.h>

#include"neuro.hpp"
#include"loader.hpp"

using namespace std;

int main() {
	int lsz[] = {1024, 2};
	int lN = sizeof(lsz) / sizeof(int);
	
	Neuro neuro( lN, lsz );
	load( "data/test_net", neuro );
	
	flt input[1024];
	flt output[2];
	
	for(int i = 0; i < 1024; ++i)
		input[i] = .5;
	
	for(int i = 0; i < 100; ++i)
		neuro.predict(input, output);
	
	cout << output[0] << '\t' << output[1] << '\n';
	
	return 0;
}




