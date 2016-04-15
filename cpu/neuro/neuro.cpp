#include"neuro.hpp"

Neuro::Neuro( int sz, int *lsz, flt ***w ) {
	init( sz, lsz, w );
}

Neuro::Neuro( const Neuro &neuro ) {
	init( neuro.layersN, neuro.layersz, neuro.weight );
}

Neuro &Neuro::operator =( const Neuro &neuro ) {
	if( weight != nullptr )
		clear();
	init( neuro.layersN, neuro.layersz, neuro.weight );
	return *this;
}

void Neuro::init( int sz, int *lsz, flt ***w ) {
	layersN = sz;
	
	layersz = (int*) malloc( layersN * sizeof(int) );
	for(int l = 0; l < layersN; ++l )
		layersz[l] = lsz[l];
	
	weight = (flt***) malloc( sizeof(flt**) * (layersN - 1) );
	for( int l = 0; l < layersN - 1; ++l ){
		weight[l] = (flt**) malloc( sizeof(flt*) * (layersz[l] + 1) ); // extra +1 for bias
		for( int i = 0; i <= layersz[l]; ++i ) {
			weight[l][i] = (flt*) malloc( sizeof(flt) * layersz[l + 1] );
			if( w != nullptr )
				for( int o = 0; o < layersz[l + 1]; ++o )
					weight[l][i][o] = w[l][i][o];
			else
				for( int o = 0; o < layersz[l + 1]; ++o )
					weight[l][i][o] = 2.0 * (flt) rand() / (flt) RAND_MAX / (flt) (layersz[l] + 1);
		}
	}
	
	linput = (flt**) malloc( layersN * sizeof( flt* ) );
	loutput = (flt**) malloc( layersN * sizeof( flt* ) );
	for( int l = 0; l < layersN; ++l ) {
		linput[l] = (flt*) malloc( layersz[l] * sizeof( flt ) );
		loutput[l] = (flt*) malloc( layersz[l] * sizeof( flt ) );
	}
}

void Neuro::clear() {
	for( int l = 0; l < layersN - 1; ++l ){
		for( int i = 0; i <= layersz[l]; ++i )
			free( weight[l][i] );
		free(weight[l] );
	}
	free( weight );
	
	for( int l = 0; l < layersN; ++l ) {
		free( linput[l] );
		free( loutput[l] );
	}
	free( linput );
	free( loutput );
	
	free( layersz );
}

Neuro::~Neuro() {
	clear();
}


flt Neuro::activation( flt x ) {
	return x;
	
	flt slope = 1.0;
	flt absx = (x > .0)? x : -x;
	return x / ( absx + 1.0 / slope );
}

void Neuro::predict( const flt *input, flt *output ) {
	// copy info to first layer
	for( int i = 0; i < layersz[0]; ++i )
		loutput[0][i] = input[i];
	
	// 		computing part
	// loop for layers
	for( int l = 0; l < layersN - 1; ++l ) {
		// applying weighted adding
		for( int o = 0; o < layersz[l + 1]; ++o )
			linput[l + 1][o] = weight[l][ layersz[l] ][o];
		
		for( int o = 0; o < layersz[l + 1]; ++o )
			for( int i = 0; i < layersz[l]; ++i )
				linput[l + 1][o] += loutput[l][i] * weight[l][i][o];
		
		// applying activation fuction
		for( int i = 0; i < layersz[l + 1]; ++i )
			loutput[l + 1][i] = activation( linput[l + 1][i] );
	}
	
	// get info from last layer
	for( int i = 0; i < layersz[layersN - 1]; ++i )
		output[i] = loutput[layersN - 1][i];
}


















