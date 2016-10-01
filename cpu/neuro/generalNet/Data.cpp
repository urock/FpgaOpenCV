//
// Created by hokop on 7/31/16.
//

#include <cstring>
#include "Data.hpp"

Data::Data(int sM, int sN, string sName) : M(sM) , N(sN), name(sName), sourcesNum(0), ownMem(false), inited(false) {}

Data::Data(const Data &data) : Data(data.M, data.N, data.name) {
	inited = true;
	ownMem = false;
	sourcesNum = data.sourcesNum;
	sourceSz = data.sourceSz;
	pixel = data.pixel;
}

Data::~Data(){
//	clearMem();
}

void Data::initMem(){
	if(ownMem)
		throw "memory is already inited";
	
	sourcesNum = 1;
	sourceSz = (int*) malloc(sizeof(int) * sourcesNum);
	sourceSz[0] = N;
	pixel = (flt****) malloc(sizeof(flt***) * sourcesNum);
	for (int k = 0; k < sourcesNum; ++k) {
		pixel[k] = (flt***) malloc(sizeof(flt**) * sourceSz[k]);
		for(int i = 0; i < sourceSz[k]; ++i){
			pixel[k][i] = (flt**) malloc(sizeof(flt*) * M);
			for(int j = 0; j < M; ++j){
				pixel[k][i][j] = (flt*) malloc(sizeof(flt) * M);
			}
		}
	}
	ownMem = true;
	inited = true;
}

void Data::resetMem(){
	if(!inited)
		throw "memory is not inited. cannot reset";
	
	for (int k = 0; k < sourcesNum; ++k)
		for(int i = 0; i < sourceSz[k]; ++i)
			for(int j = 0; j < M; ++j)
				memset(pixel[k][i][j], 0, M * sizeof(flt));
}

void Data::clearMem(){
	if(!ownMem)
		throw "memory is not inited. cannot clear";
	
	for (int k = 0; k < sourcesNum; ++k) {
		for(int i = 0; i < sourceSz[k]; ++i)
			for(int j = 0; j < M; ++j){
				free(pixel[k][i][j]);
			}
	}
	for (int l = 0; l < sourcesNum; ++l) {
		for(int i = 0; i < sourceSz[l]; ++i)
			free(pixel[l][i]);
	}
	for(int i = 0; i < sourcesNum; ++i)
		free(pixel[i]);
	free(pixel);
	
	sourcesNum = 0;
	ownMem = false;
}

Data Data::operator=(Data source){
	if(ownMem)
		clearMem();
	inited = true;
	M = source.M;
	N = source.N;
	sourcesNum = source.sourcesNum;
	sourceSz = source.sourceSz;
	pixel = source.pixel;
	name = source.name;
	return *this;
}

Data Data::range(int i1, int i2) {
	if(!inited)
		throw "error []: memory is not inited";
	if(sourcesNum == 1) {
		Data tmp = *this;
		tmp.N = i2 - i1 + 1;
		tmp.sourcesNum = 1;
		tmp.sourceSz = (int*) malloc(sizeof(int));
		tmp.sourceSz[0] = tmp.N;
		tmp.pixel[0] = &pixel[0][i1];
		return tmp;
	}
	
	Data *datas = (Data*) malloc(sourcesNum * sizeof(Data));
	for (int i = 0; i < sourcesNum; ++i) {
		datas[i].sourcesNum = 1;
		datas[i].sourceSz = (int*) malloc(sizeof(int));
		datas[i].N = sourceSz[i];
		datas[i].sourceSz[0] = sourceSz[i];
		datas[i].M = M;
		datas[i].pixel = (flt****) malloc(sizeof(flt***));
		datas[i].pixel[0] = pixel[i];
	}
	
	int mapsPassed = 0;
	int startI = -1, endI = -1;
	for (int i = 0; i < sourcesNum; ++i) {
		mapsPassed += datas[i].N;
		int sI = 0;
		int eI = datas[i].N - 1;
		
		if (mapsPassed > i1 && startI < 0){
			startI = i;
			sI = i1 - (mapsPassed - datas[i].N);
		}
		if (mapsPassed > i2 && endI < 0){
			endI = i;
			eI = i2 - (mapsPassed - datas[i].N);
		}
		datas[i] = datas[i].range(sI, eI);
	}
	
	Data tmp = datas[startI];
	for (int i = startI + 1; i <= endI; ++i) {
		tmp = tmp + datas[i];
	}
	return tmp;
}

Data Data::operator+(Data data) {
	if(data.M != M)
		throw "pic sizes do not match";
	
	Data tmp(M, N + data.N, name + string(" and ") + data.name);
	
	tmp.sourcesNum = sourcesNum + data.sourcesNum;
	tmp.sourceSz = (int*) malloc(sizeof(int) * tmp.sourcesNum);
	
	tmp.pixel = (flt****) malloc(sizeof(flt***) * tmp.sourcesNum);
	
	for(int i = 0; i < sourcesNum; ++i){
		tmp.sourceSz[i] = sourceSz[i];
		tmp.pixel[i] = pixel[i];
	}
	
	for(int i = sourcesNum; i < tmp.sourcesNum; ++i){
		tmp.sourceSz[i] = data.sourceSz[i];
		tmp.pixel[i] = data.pixel[i];
	}
	
	return tmp;
}

flt &Data::at(int map, int x, int y){
	int targetSource = 0;
	int mapsPassed = 0;
	for(int i = 0; i < sourcesNum; ++i){
		mapsPassed += sourceSz[i];
		if(mapsPassed > map){
			targetSource = i;
			mapsPassed -= sourceSz[i];
			break;
		}
	}
	return pixel[targetSource][map - mapsPassed][x][y];
}




















