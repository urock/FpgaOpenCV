
#include <string.h>
#include <stdio.h>
#include "neuro.h"




void neuro_top(volatile float_8_t *ddr_base ) {

#pragma HLS INTERFACE m_axi port=ddr_base offset=direct
#pragma HLS DATA_PACK variable=ddr_base struct_level


   float local_buf[N];

   float_8_t data_in;
#pragma HLS DATA_PACK variable=data_in struct_level

   loop_in_1:for (int i = 0; i < N/8; i++) {
      data_in = *(ddr_base + i);
      loop_in_2: for (int j = 0; j < 8; j++)
         local_buf[i*8 + j] = data_in.flt[i];
   }


    loop_comp: for (int l = 0; l < layersN; l++)
      compLayer(local_buf, l, ddr_base, local_buf);


   loop_out_1:for (int i = 0; i < N/8; i++) {

      loop_out_2: for (int j = 0; j < 8; j++)
         data_in.flt[i] = local_buf[i*8 + j];

       *(ddr_base + i) = data_in;
   }


   // тут что-то нужно сделать с результатом, выделить из него признак, нашли или нет объект.

}


void compLayer(float *data_in, int layer_num, volatile float_8_t *ddr_base, float *data_out) {



   float     w_in[N/P][P];
#pragma ARRAY_PARTITION linputs -dim 2 complete

   float     linputs[N/P][P];
#pragma ARRAY_PARTITION linputs -dim 2 complete

   // load weights and make calc
   c_loop_i: for (int i = 0; i < N; ++i) {

#pragma HLS_DATAFLOW

      float data_in_val = data_in[i];

   // для каждого входного данного надо подгрузить из памяти N весов
      memcpy(w_in, (float_8_t*)(ddr_base + layer_num*N*N/P + i*N/P), sizeof(float_8_t)*N/P);
   // пусть у нас будет P параллельных вычислителей, тогда это два следующих вложенных цикла
      c_loop_j: for (int j = 0; j < N/P; j++) {
#pragma HLS_PIPELINE

         c_loop_k: for (int k = 0; k < P; ++k) {

            float w = w_in[j][k];

            //ap_uint<16> w = wide_weight.Range((k+1)*P - 1,k*P);

            if (i == 0)
               linputs[j][k] = w*data_in_val;
            else
               linputs[j][k] += w*data_in_val;

         } // k
      } // j
   } // i


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


// typedef struct {
//    float d0;
//    float d1;
// } two_floats;


// union long_float{
//    uint64_t A;
//    two_floats B;
// };


//    volatile uint64_t  *stream1;

//    long_float temp;
//    two_floats rand_buf2d;

//       temp.A      = *stream1;
//       rand_buf2d  = temp.B;
