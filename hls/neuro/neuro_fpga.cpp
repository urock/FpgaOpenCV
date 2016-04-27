

// let N be the length of input array == number of neurons in each layer
// N = 32*32 = 1024

#define N      1024
#define P      16       // параллельных вычислителей PE (processing elements)


typedef ap_uint<256>    wide_t;
typedef int             input_t;


// пока только для одного слоя
void dummy_func(ap_int<256> *ddr_base ) {


   short img_in[N];  // 2 bytes per pixel

   //weight_t w[N/P];

   wide_t      w_in[N/P];

   memcpy(img_in, ddr_base + image_offset, 2*N);

   input_t     linputs[N/P][P];
#pragma HLS_PARTITION linputs -dim 1 complete

   // load weights and make calc
   for (int i = 0; i < N; ++i) {

#pragma HLS_DATAFLOW

   // для каждого входного данного надо подгрузить из памяти N весов
      memcpy(w_in, ddr_base + weight_offset + i*2*N, 2*N);
   // пусть у нас будет P = 16 параллельных вычислителей, тогда это два следующих вложенных цикла
      for (int j = 0; j < N/P; j++) {
#pragma HLS_PIPELINE

         wide_t wide_weight = w_in[j];

         for (int k = 0; k < P; ++k) {

            ap_uint<16> w = wide_weight.Range((k+1)*P - 1,k*P);

            if (first_layer)
               linputs[j][k] = w*img_in[i];
            else
               linputs[j][k] += w*img_in[i];




         } // k

      } // j


   } // i


}

// Какой у меня интерфейс к памяти на microZed

// 32 bits * 1 GT/s = 4 GB/s

// 320 bits * 100 MT/s

// 256 bits * 100 MHz

// тип данных для весов - 16 бит. 256/16 = 16 параллельных операций