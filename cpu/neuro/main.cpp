#include<iostream>
#include<time.h>

#include"neuro.hpp"
#include"descriptor.hpp"
#include"teacher.hpp"

using namespace std;
using namespace cv;

int main() {
	int lsz[] = {3, 2, 1};
	int lN = sizeof(lsz) / sizeof(int);
	
	Neuro neuro( lN, lsz );
	
	Descriptor des( neuro );
	des.save( "data/before" );
	cout << "data saved\n";
	
	flt input[] = {.1, .1, .1};
	flt output[1];
	
	neuro.predict(input, output);
	//cout << output[0] << '\t' << output[1] << '\n';
	
	Teacher teacher(neuro);
	
	vec inputV, theory;
	for( int i = 0; i < lsz[0]; ++i )
		inputV.push_back( input[i] );
	
	theory.push_back(.1);
	
	for( int i = 0; i < 1000010; ++i ) {
		int sum = 0;
		for( int k = 0; k < lsz[0]; ++k ) {
			int s = rand() % 2;
			sum += s;
			inputV[k] = s;
		}
		
		if( sum == 1 )
			theory[0] = .5;
		else
			theory[0] = .0;
		
		teacher.teach(inputV, theory);
		neuro.predict(&inputV[0], output);
		if(i > 1000000)
			cout << i << '\t' << sum << '\t' << output[0] << '\n';
	}
	
	des.save( "data/after" );
	cout << "data saved\n";
	imwrite( "data/tst.png", des.getImage() );
	cout << "pic saved\n";
	
	return 0;
}
