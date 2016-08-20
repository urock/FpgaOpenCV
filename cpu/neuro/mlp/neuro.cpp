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
					weight[l][i][o] = ( 2.0 * ( (flt) rand() / (flt) RAND_MAX ) - 1.0)
							/ sqrt((flt) (layersz[l] + 1));
		}
	}
	
	lreg = (flt**) malloc( layersN * sizeof( flt* ) );
	for( int l = 0; l < layersN; ++l ) {
		lreg[l] = (flt*) malloc( layersz[l] * sizeof( flt ) );
	}
}

void Neuro::clear() {
	for( int l = 0; l < layersN - 1; ++l ){
		for( int i = 0; i <= layersz[l]; ++i )
			free( weight[l][i] );
		free(weight[l] );
	}
	free( weight );
	
	for( int l = 0; l < layersN; ++l )
		free( lreg[l] );
	free( lreg );
	
	free( layersz );
}

Neuro::~Neuro() {
	clear();
}


flt Neuro::activation( flt x ) {
	if( x < activationCutoff )
		x = activationCutoff;
	
	flt ex = exp(-x);
	return (1.0 - ex) / (1.0 + ex);
}

flt Neuro::activationDeriv( flt x ) {
	if( x < activationCutoff )
		x = activationCutoff;
	
	flt ex = exp(-x);
	flt s = 1.0 + ex;
	return 2.0 * ex / (s*s);
}


// N - input layer size
// K - output layer size
void Neuro::compLayer( float *data_in, float **weight_in, int N, int K, float *data_out ) {
	// calc inputs to layer j+1
	for (int k = 0; k < K; ++k )
		data_out[k] = weight_in[N][k];
	
	// weighted adding
	for (int n = 0; n < N; ++n )
		for (int k = 0; k < K; ++k )
			data_out[k] += data_in[n] * weight_in[n][k];
	
	// calc outputs
	for (int k = 0; k < K; ++k )
		data_out[k] = activation (data_out[k]);
}

void Neuro::predict( const flt *input, flt *output ) {
	// copy info to first layer
	for( int i = 0; i < layersz[0]; ++i ) {
		lreg[0][i] = input[i];
	}
	
	// 		computing part
	// loop for layers
	for( int l = 0; l < layersN - 1; ++l ) {
		compLayer( lreg[l], weight[l], layersz[l], layersz[l + 1], lreg[l + 1] );
	}
	
	// get info from last layer
	for( int i = 0; i < layersz[layersN - 1]; ++i )
		output[i] = lreg[layersN - 1][i];
}
















