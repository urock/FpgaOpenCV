#include<iostream>
#include<time.h>

#include"neuro.hpp"
#include"descriptor.hpp"

using namespace std;
using namespace cv;

int main() {
	int lsz[] = {3, 2048, 2};
	int lN = sizeof(lsz) / sizeof(int);
	
	Neuro neuro( lN, lsz );
	
	Descriptor des( neuro );
	//des.save( "data/neuro1" );
	cout << "data saved\n";
	
	//imwrite( "data/tst.png", des.getImage() );
	cout << "pic saved\n";
	
	flt input[] = {1.0, 1.0, 1.0};
	flt output[2];
	neuro.predict(input, output);
	cout << output[0] << '\t' << output[1] << '\n';
	
	return 0;
}
