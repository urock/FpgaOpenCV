//
// Created by hokop on 7/31/16.
//

#ifndef GENERALIZEDNET_FMA_H
#define GENERALIZEDNET_FMA_H

#include<string>

using namespace std;

typedef float flt;

/** FEATURE MAP ARRAY */
class Data
{
public:
	Data() : ownMem(false), inited(false), name("") {};
	Data(int sM, int sN, string sName = "");
	Data(const Data &data);
	~Data();
	
	void initMem();
	void resetMem();
	void clearMem();
	void copyFrom(Data &source);
	
	Data operator=(Data source);
	Data range(int i1, int i2);
	Data operator+(Data data);
	
	flt &at(int map, int x, int y);
	
	string name = "";
	int M; // size of map
	int N; // number of maps
	
	int sourcesNum;
	int *sourceSz;
	bool ownMem;
	bool inited;
	
	flt ****pixel; // [source] [map] [x] [y]
};

#endif //GENERALIZEDNET_FMA_H
