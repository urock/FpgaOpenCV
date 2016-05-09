
#include "top.h"


void simple_pass_through_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM) {

#pragma HLS INTERFACE axis port=INPUT_STREAM
#pragma HLS INTERFACE axis port=OUTPUT_STREAM

#pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"


    RGB_IMAGE img_0(MAX_HEIGHT, MAX_WIDTH);

#pragma HLS dataflow
    hls::AXIvideo2Mat(INPUT_STREAM, img_0);


    hls::Mat2AXIvideo(img_0, OUTPUT_STREAM);
}
