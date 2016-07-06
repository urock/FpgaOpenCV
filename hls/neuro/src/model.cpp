

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
      memcpy(w_in, weights_in + layer_num*N*N + i*N, sizeof(float)*N);

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
