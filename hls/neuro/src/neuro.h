#ifndef NEURO_H
#define NEURO_H

#include <string.h>
#include <stdio.h>
#include "ap_int.h"
#include "ap_fixed.h"


// let N be the length of input array == number of neurons in each layer
// N = 32*32 = 1024
#define L 		32		// линейный размер объекта
#define N      (L*L)
#define P      8       // параллельных вычислителей PE (processing elements)
#define	D		(L/P)	// 4 - глубина массива для memcpy


// Какой у меня интерфейс к памяти на microZed

// 32 bits * 1 GT/s = 4 GB/s

// 320 bits * 100 MT/s

// 256 bits * 100 MHz

// Если использовать тип данных для весов - 16 бит. 256/16 = 16 параллельных операций



#define layersN 3



typedef ap_uint<256> ddr_bus;


typedef struct {
	float d[8];
} floats;


 union int_float{
	unsigned int 	A;
    float 			B;
 };


float activation(float x);
void compLayer(float *data_in, int layer_num, volatile ddr_bus *ddr_base, float *data_out);
void neuro_top(volatile ddr_bus *ddr_base );


#endif // NEURO_H
