#include"teacher.hpp"

Teacher::Teacher( Neuro &n ) : neuro(n) {}

void Teacher::teachLayer( const vec &inputVal, int outputSz, const vec &deriv,
		flt **weight, int l, vec &nextDeriv )
{
	// prepare some values
	vec s(outputSz, .0);
	for( int o = 0; o < outputSz; ++o ) {
		for( int i = 0; i < inputVal.size(); ++i )
			s[o] += weight[i][o] * inputVal[i];
		s[o] = neuro.activationDeriv( s[o] );
	}
	
	// correct weights
	for( int o = 0; o < outputSz; ++o )
		for( int i = 0; i < inputVal.size(); ++i ) {
			flt edio = deriv[o] * s[o] * inputVal[i];
			weight[i][o] -= speed * edio; // correction here
		}
	
	// calc derivatives for next layer
	for( int i = 0; i < inputVal.size(); ++i ) {
		flt edai = 0;
		for( int k = 0; k < outputSz; ++k )
			edai += deriv[k] * weight[i][k] * s[k];
		nextDeriv.push_back( edai ); // edai * 1.0 is default
	}
	
	return;
}

void Teacher::teach( const vec &input, const vec &theory ) {
	// prepare arrays
	vec output( neuro.layersz[ neuro.layersN - 1 ], 0 );
	neuro.predict( &input[0], &output[0] );
	
	vec ed( errorDeriv( output, theory ) );
	
	for( int l = neuro.layersN - 1; l > 0; --l ) {
		int ls = neuro.layersz[ l - 1 ];
		
		vec nextD;
		vec inputVal( ls, .0 );
		for( int i = 0; i < ls; ++i )
			inputVal[i] = neuro.lreg[l - 1][i];
		inputVal.push_back(1.0);
		
		teachLayer( inputVal, neuro.layersz[l], ed, neuro.weight[l - 1], l - 1, nextD );
		
		ed = nextD;
	}
	
	return;
}

vec Teacher::errorDeriv( const vec &real, const vec &theory ) {
	vec ed;
	for( int i = 0; i < real.size(); ++i ) {
		flt a = real[i] - theory[i];
		ed.push_back( a );
	}
	return ed;
}

//flt Teacher::error( const vec &real, const vec &theory ) {
//	flt e = 0;
//	for( int i = 0; i < real.size(); ++i ){
//		flt a = real[index] - theory[index];
//		e += a * a;
//	}
//	return e;
//}
