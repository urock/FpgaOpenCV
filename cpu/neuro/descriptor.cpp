#include"descriptor.hpp"

void Descriptor::load( string filename ) {
	ifstream f( filename.c_str() );
	string line;
	vector<string> parsed;
	
	getline( f, line );
	
	parsed = parseLine(line);
	int layersN = parsed.size();
	int *layersz = (int*) malloc( layersN * sizeof(int) );
	
	for(int l = 0; l < layersN; ++l ) {
		layersz[l] = atoi( parsed[l].c_str() );
	}
	
	if( neuro.weight != nullptr )
		neuro.clear();
	neuro.init( layersN, layersz );
	
	for( int l = 0; l < layersN - 1; ++l ){
		for( int i = 0; i <= layersz[l]; ++i ) {
			getline( f, line );
			parsed = parseLine( line );
			for( int o = 0; o < layersz[l + 1]; ++o )
				neuro.weight[l][i][o] = atof( parsed[o].c_str() );
		}
	}
	
	free(layersz);
	
	f.close();
	return;
}

void Descriptor::save( string filename ) {
	ofstream f( filename.c_str() );
	
	for( int l = 0; l < neuro.layersN; ++l )
		f << neuro.layersz[l] << '\t';
	f << endl;
	
	for( int l = 0; l < neuro.layersN - 1; ++l ) {
		for( int i = 0; i <= neuro.layersz[l]; ++i ) {
			for( int o = 0; o < neuro.layersz[l + 1]; ++o ) {
				f << neuro.weight[l][i][o] << '\t';
			}
			f << '\n';
		}
	}
	f.close();
	return;
}

std::vector<string> parseLine(string line) {
	std::vector<string> parsed;
	bool split = true;
	string temp = "";
	
	for( int i = 0; i < line.length(); ++i ) {
		char c = line[i];
		if( c == ' ' || c == '\t' ) {
			if( !split ) {
				parsed.push_back(temp);
				temp = "";
			}
			split = true;
		} else {
			split = false;
			temp += c;
		}
	}
	if( !split )
		parsed.push_back(temp);
	
	return parsed;
}

float sigmoid(float x, float slope) {
	return x / ( fabs(x) + 1.0 / slope );
}

Scalar colorTran( float x, float slope ) {
	slope /= 2.0;
	int b = 0, r = 0;
	if( x > .0 )
		r = 255 * sigmoid( x, slope );
	else
		b = 255 * sigmoid( -x, slope );
	return Scalar(255 - r, 255 - r - b, 255 - b);
}

Mat Descriptor::getImage( ) {
	int width = 1920;
	int height = 1080;
	int lN = neuro.layersN;
	int x[ lN ];
	int dx = width / (lN + 1);
	
	for( int i = 0; i < lN; ++i )
		x[i] = dx * (i + 1);
	
	Mat mat( height, width, CV_8UC3, Scalar(255, 255, 255) );
	
	vector< vector<int> > y;
	
	for( int i = 0; i < lN; ++i ) {
		int nN = neuro.layersz[i];
		int dy = height / (nN + 1);
		vector<int> yi;
		for( int k = 0; k < nN; ++k )
			yi.push_back( dy * (k + 1) );
		y.push_back( yi );
	}
	
	for( int i = 0; i < lN - 1; ++i ) {
		int ni = neuro.layersz[i];
		int no = neuro.layersz[i + 1];
		for( int j = 0; j < ni; ++j )
			for( int k = 0; k < no; ++k ) {
				line(mat, Point( x[i], y[i][j] ), Point( x[i + 1], y[i + 1][k] ),
						colorTran(neuro.weight[i][j][k], ni), 2 );
			}
	}
	
	for( int l = 0; l < lN - 1; ++l ) {
		int ni = neuro.layersz[l];
		int no = neuro.layersz[l + 1];
		int rad = 8;
		for( int o = 0; o < no; ++o )
			circle(mat, Point( x[l + 1], y[l + 1][o] ), rad, colorTran(neuro.weight[l][ni][o], ni), -1 );
	}
	
	return mat;
}












