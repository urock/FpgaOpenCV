
#include "top.h"


void simple_pass_through_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM, int apply_filter) 
{

#pragma HLS INTERFACE axis port=INPUT_STREAM
#pragma HLS INTERFACE axis port=OUTPUT_STREAM

#pragma HLS RESOURCE core=AXI_SLAVE variable=apply_filter metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"

#pragma HLS INTERFACE ap_stable port=apply_filter


    RGB_IMAGE img_in(MAX_HEIGHT, MAX_WIDTH);
    RGB_IMAGE img_1(MAX_HEIGHT, MAX_WIDTH);		
    RGB_IMAGE img_0(MAX_HEIGHT, MAX_WIDTH);
    RGB_IMAGE img_res(MAX_HEIGHT, MAX_WIDTH);

#pragma HLS dataflow
    hls::AXIvideo2Mat(INPUT_STREAM, img_in);

	hls::Duplicate(img_in,img_0,img_1);    

    r_loop: for(int row = 0; row < MAX_HEIGHT; row++) {
#pragma HLS loop_flatten off
       c_loop: for(int col = 0; col < MAX_WIDTH; col++) {
#pragma HLS pipeline II=1

            RGB_PIXEL p;

            img_1 >> p;

            p.val[0] = 255;

			img_res << p;

        }
    }



	if (apply_filter)
		hls::Mat2AXIvideo(img_res, OUTPUT_STREAM);
	else
		hls::Mat2AXIvideo(img_0, OUTPUT_STREAM);	


}
