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
	Teacher( Neuro &n ) : neuro(n) {}
	
	Neuro &neuro;
	flt speed = 0.2;
	
//	flt error( const vec &real, const vec &theory );
	vec errorDeriv( const vec &real, const vec &theory );
	
	void teachLayer( const vec &inputVal, int outputSz, const vec &deriv, flt **weight, vec &nextDeriv );
	void teach( const vec &input, const vec &theory );
};

#endif //TEACHER

