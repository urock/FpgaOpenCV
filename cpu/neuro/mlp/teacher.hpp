#ifndef TEACHER
#define TEACHER

#include<vector>
#include<iterator>
#include<cmath>

#include"neuro.hpp"

using namespace std;

typedef vector<flt> vec;

struct Teacher
{
	Teacher( Neuro &n );
	
	Neuro &neuro;
	flt speed = .001;
	// .0005 was ok last time
	
//	flt error( const vec &real, const vec &theory );
	vec errorDeriv( const vec &real, const vec &theory );
	
	void teachLayer( const vec &inputVal, int outputSz, const vec &deriv, flt **weight, int l, vec &nextDeriv );
	void teach( const vec &input, const vec &theory );
	void apply();
};

#endif //TEACHER

