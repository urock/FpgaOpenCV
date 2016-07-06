
#include "neuro.h"


void neuro_top(volatile ddr_bus *ddr_base, float buf_out[N] ) {

#pragma HLS INTERFACE m_axi port=ddr_base offset=direct
#pragma HLS DATA_PACK variable=ddr_base struct_level


   float local_buf[N];

   ddr_bus 	input_buffer[D];

   int_float ift;


   for (int i = 0; i < L; i++) {

		memcpy(input_buffer, (ddr_bus*)(ddr_base + i*D), sizeof(input_buffer));

		   for (int k=0; k<D; k++) {
			   for (int l=0; l<P; l++) {
				   unsigned int temp32;
				   temp32 = input_buffer[k].range(31+32*l,32*l);
				   ift.A = temp32;
				   local_buf[i*32 +k*8 +l] = ift.B;
			   }
		   }



   }



    loop_comp: for (int l = 0; l < layersN; l++)
      compLayer(local_buf, l, ddr_base, local_buf);


   loop_out_1:for (int i = 0; i < N; i++) {

	   buf_out[i] = local_buf[i];

//      loop_out_2: for (int j = 0; j < 8; j++)
//    	  temp.B.d[i] = local_buf[i*8 + j];
//
//       *(ddr_base + i) = temp.A;
   }


   // тут что-то нужно сделать с результатом, выделить из него признак, нашли или нет объект.

}


void compLayer(float *data_in, int layer_num, volatile ddr_bus *ddr_base, float *data_out) {



	   ddr_bus 	w_input_buffer[D];
#pragma HLS ARRAY_PARTITION variable=w_input_buffer complete dim=1

	   int_float ift;


   float     linputs[L*D][P];
#pragma HLS ARRAY_PARTITION variable=linputs complete dim=2
//#pragma ARRAY_PARTITION linputs -dim 2 complete

   // load weights and make calc
   l1: for (int i = 0; i < N; ++i) {

	   float data_in_val = data_in[i];

	   l2: for (int j = 0; j < L; ++j) {
#pragma HLS DATAFLOW
 // подгружаем веса блоками по D*P, всего таких блоков будет L

		   memcpy(w_input_buffer, (ddr_bus*)(ddr_base + 0x1000000 + layer_num*N*N/P + i*N/P + j*D), sizeof(w_input_buffer));

		   l3: for (int k=0; k<D; k++) {
#pragma HLS PIPELINE

			   l4: for (int l=0; l<P; l++) {
				   unsigned int temp32;
				   temp32 = w_input_buffer[k].range(31+32*l,32*l);
				   ift.A = temp32;

		            if (i == 0)
		               linputs[j*4 + k][l] = ift.B*data_in_val;
		            else
		               linputs[j*4 + k][l] += ift.B*data_in_val;

			   } //l4
		   } // l3
	   } // l2
   } // l1


   int l = 0;
   // calc outputs of neurons
   c_loop_o1: for (int j = 0; j < N/P; ++j) {
 #pragma HLS_PIPELINE
      // этот цикл тоже может быть распараллелен
      c_loop_o2: for (int k = 0; k < P; ++k) {
         data_out[l++] = activation(linputs[j][k]);
      }
   }

}

float activation(float x) {
   return x;
}

