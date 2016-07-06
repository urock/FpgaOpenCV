/***************************************************************************

*   © Copyright 2013 Xilinx, Inc. All rights reserved. 

*   This file contains confidential and proprietary information of Xilinx,
*   Inc. and is protected under U.S. and international copyright and other
*   intellectual property laws. 

*   DISCLAIMER
*   This disclaimer is not a license and does not grant any rights to the
*   materials distributed herewith. Except as otherwise provided in a valid
*   license issued to you by Xilinx, and to the maximum extent permitted by
*   applicable law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND WITH
*   ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES AND CONDITIONS, 
*   EXPRESS, IMPLIED, OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES
*   OF MERCHANTABILITY, NON-INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR 
*   PURPOSE; and (2) Xilinx shall not be liable (whether in contract or 
*   tort, including negligence, or under any other theory of liability)
*   for any loss or damage of any kind or nature related to, arising under
*   or in connection with these materials, including for any direct, or any
*   indirect, special, incidental, or consequential loss or damage (including
*   loss of data, profits, goodwill, or any type of loss or damage suffered 
*   as a result of any action brought by a third party) even if such damage
*   or loss was reasonably foreseeable or Xilinx had been advised of the 
*   possibility of the same. 

*   CRITICAL APPLICATIONS 
*   Xilinx products are not designed or intended to be fail-safe, or for use
*   in any application requiring fail-safe performance, such as life-support
*   or safety devices or systems, Class III medical devices, nuclear facilities,
*   applications related to the deployment of airbags, or any other applications
*   that could lead to death, personal injury, or severe property or environmental
*   damage (individually and collectively, "Critical Applications"). Customer
*   assumes the sole risk and liability of any use of Xilinx products in Critical
*   Applications, subject only to applicable laws and regulations governing 
*   limitations on product liability. 

*   THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS PART OF THIS FILE AT 
*   ALL TIMES.

***************************************************************************/
#include "top.h"

#define ABSDIFF(x,y)	((x>y)? x - y : y - x)
#define ABS(x)          ((x>0)? x : -x)
#define SEPIA_DEPTH     30

unsigned char rgb2y(RGB_PIXEL rgb)
{

//#pragma HLS LATENCY min=5
#pragma HLS pipeline II=1

  unsigned char R = rgb.val[0];
  unsigned char G = rgb.val[1];
  unsigned char B = rgb.val[2];

  unsigned short R1 = 66*R;
#pragma HLS RESOURCE variable=R1 core=Mul
  unsigned short G1 = 129*G;
#pragma HLS RESOURCE variable=G1 core=Mul
  unsigned short B1 = 25*B;
#pragma HLS RESOURCE variable=B1 core=Mul
  unsigned short S1 = R1 + G1;
  unsigned short S2 = B1 + 128;

  unsigned short S = S1 + S2;

  unsigned char y = (S >> 8) + 16;

  //unsigned char y = ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16;

  return y;
}

RGB_PIXEL sepia_filter(RGB_PIXEL rgb)
{
  RGB_PIXEL sepia;

  const int depth = SEPIA_DEPTH;

  short B;
  short R;
  short G;

  B = (rgb.val[2] + rgb.val[1] + rgb.val[0]) / 3;
  R = B + 2*depth;
  G =  B + depth + 4;
  sepia.val[0] = (unsigned char) B;
  if(R > 255)
    sepia.val[2] = 255;
  else
    sepia.val[2] = (unsigned char) R;
  if(G > 255)
    sepia.val[1] = 255;
  else
    sepia.val[1] = (unsigned char) G;


  return sepia;
}


unsigned char sobel_operator(unsigned char y_window[3][3])
{
  short x_weight = 0;
  short y_weight = 0;

  short edge_weight;
  unsigned char edge_val;

  int i;
  int j;


  const char x_op[3][3] = { {-1,0,1},
			    {-2,0,2},
			    {-1,0,1}};

  const char y_op[3][3] = { {1,2,1},
			    {0,0,0},
			    {-1,-2,-1}};

  //Compute approximation of the gradients in the X-Y direction
  y_dir_sobel:for(i = 0; i < 3; i++){


  x_dir_sobel: for(j = 0; j < 3; j++){

      // X direction gradient
      x_weight = x_weight + (y_window[i][j] * x_op[i][j]);

      // Y direction gradient
      y_weight = y_weight + (y_window[i][j] * y_op[i][j]);

    }
  }

  edge_weight = ABS(x_weight) + ABS(y_weight);

  edge_val = (255-(unsigned char)(edge_weight));
  if(edge_val > 200)
    edge_val = 0;
  else if(edge_val < 50)
    edge_val = 255;
  return edge_val;
}

#define K_WIDTH 3
#define K_HEIGHT 3

void image_filter(AXI_STREAM& INPUT_STREAM, AXI_STREAM& OUTPUT_STREAM, int apply_filter) {
    //Create AXI streaming interfaces for the core
#pragma HLS INTERFACE axis port=INPUT_STREAM
#pragma HLS INTERFACE axis port=OUTPUT_STREAM

#pragma HLS RESOURCE core=AXI_SLAVE variable=apply_filter metadata="-bus_bundle CONTROL_BUS"
#pragma HLS RESOURCE core=AXI_SLAVE variable=return metadata="-bus_bundle CONTROL_BUS"

#pragma HLS INTERFACE ap_stable port=apply_filter

const int rows = MAX_HEIGHT;
const int cols = MAX_WIDTH;



    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> 	img_0(rows, cols);
    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3> 	img_1(rows, cols);
	

//    hls::Mat<MAX_HEIGHT,MAX_WIDTH,HLS_8UC3>      src1(rows,cols);
//    hls::Mat<MAX_HEIGHT, MAX_WIDTH, HLS_8UC3>   _src(rows,cols);

	
#pragma HLS dataflow
    hls::AXIvideo2Mat(INPUT_STREAM, img_0);
    //hls::AXIvideo2Mat(INPUT_STREAM, _src);
	//hls::Duplicate(_src,img_0,src1);

    unsigned char edge_val;
    unsigned char y;
    unsigned char y_window[K_HEIGHT][K_WIDTH];
    RGB_PIXEL line_buffer[3][MAX_WIDTH+(K_WIDTH/2)];
#pragma AP array_partition variable=line_buffer complete dim=1

    assert(rows <= MAX_HEIGHT);
    assert(cols <= MAX_WIDTH);
    // Note the expanded iteration space.
    int flag = 0;
    r_loop: for(int row = 0; row < rows + K_HEIGHT/2; row++) {
#pragma HLS loop_flatten off
       c_loop: for(int col = 0; col < cols + K_WIDTH/2; col++) {
#pragma HLS pipeline II=1

            RGB_PIXEL p;
            RGB_PIXEL pix;

            if(row < rows && col < cols) {
                img_0 >> p;
            }

            for(int i = 0; i < 3; i++) {
                y_window[i][2] = y_window[i][1];
                y_window[i][1] = y_window[i][0];
            }

            y_window[2][0] = rgb2y(line_buffer[2][col] = line_buffer[1][col]);
            y_window[1][0] = rgb2y(pix = line_buffer[1][col] = line_buffer[0][col]);
            y_window[0][0] = rgb2y(line_buffer[0][col] = p);

            int output_row = row-K_HEIGHT/2;
            int output_col = col-K_WIDTH/2;

            // Handle the boundary condition where we can't effectively detect edges.
            if(output_row == 0 || output_col == 0 || output_row == (rows-1) || output_col == (cols-1)){
                edge_val = 0;
            } else {
                edge_val = sobel_operator(y_window);
            }

            RGB_PIXEL sepia = sepia_filter(pix);
            RGB_PIXEL result = sepia;

            result.val[0] += edge_val;
            result.val[1] += edge_val;
            result.val[2] += edge_val;

            // Account for the spatial shift introduced by the filter.
            if(output_row >= 0 && output_col >= 0) {
                img_1 << result;
            }
        }
    }
	
//	if (apply_filter)
//		hls::Mat2AXIvideo(img_1, OUTPUT_STREAM);
//	else
//		hls::Mat2AXIvideo(src1, OUTPUT_STREAM);

	hls::Mat2AXIvideo(img_1, OUTPUT_STREAM);
}
