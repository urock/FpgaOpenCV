

// let N be the length of input array == number of neurons in each layer
// N = 32*32 = 1024

#define N      1024
#define P      16       // параллельных вычислителей PE (processing elements)


// Какой у меня интерфейс к памяти на microZed

// 32 bits * 1 GT/s = 4 GB/s

// 320 bits * 100 MT/s

// 256 bits * 100 MHz

// Если использовать тип данных для весов - 16 бит. 256/16 = 16 параллельных операций




#define layersN 3

void predict(float *image_in, float *weights_in, float *result) {

   float local_buf[N];

   // загружаем картинку 32*32 из DDR в локальный буфер BRAM
   memcpy(local_buf, image_in, sizeof(float)*N);

   for (int l = 0; l < layersN; l++)
      compLayer(local_buf, l, weights_in, local_buf);

   // тут что-то нужно сделать с результатом, выделить из него признак, нашли или нет объект.



}


void compLayer(float *data_in, int layer_num, float *weights_in, float *data_out) {

   float       w_in[N/P][P];
   float       linputs[N/P][P];

   // load weights and make calc
   for (int i = 0; i < N; ++i) {

      float data_in_val = data_in[i];

      // для каждого входного данного надо подгрузить из памяти N весов
      memcpy(w_in, weights_in + layer_num*sizeof(float)*N*N + i*sizeof(float)*N, sizeof(float)*N);

      // пусть у нас будет P = 16 параллельных вычислителей, тогда это два следующих вложенных цикла
      for (int j = 0; j < N/P; ++j) {

         // этот цикл будет развернут и выполнен параллельно
         // средствами HLS будет обеспечен одновременный доступ ко всем элементам второго измерения массивов w_in и linputs
         // кстати на CPU, где поддерживаются векторные операции тут тоже можно добиться параллельности
         for (int k = 0; k < P; ++k) {

            float w = w_in[j][k];

            if (i == 0)
               linputs[j][k] = w*data_in_val + initial_weight;
            else
               linputs[j][k] += w*data_in_val;

         } // k
      } // j
   } // i

   int l = 0;
   // calc outputs of neurons
   for (int j = 0; j < N/P; ++j) {
      // этот цикл тоже может быть распараллелен
      for (int k = 0; k < P; ++k) {
         data_out[l++] = activation(linputs[j][k]);
      }
   }

}





typedef ap_uint<256>    wide_t;
typedef int             input_t;


// пока только для одного слоя
void dummy_func_hls(ap_int<256> *ddr_base ) {


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