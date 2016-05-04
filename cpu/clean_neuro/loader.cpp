#include"loader.hpp"

void load( string filename, Neuro &neuro ) {
	ifstream f( filename.c_str() );
	
	if( ! f.is_open() ) {
		return;
	}
	
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









