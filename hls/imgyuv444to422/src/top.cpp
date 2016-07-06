#include "hls_video.h"
//#include "hls_opencv.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
const int rows = 1080;
const int cols = 1920;

typedef hls::stream<ap_axiu<16,1,1,1> > AXI_STREAM2;
typedef hls::stream<ap_axiu<24,1,1,1> > AXI_STREAM3;
typedef hls::Mat<rows, cols, HLS_8UC3> YUV_IMAGE_444;
typedef hls::Mat<rows, cols, HLS_8UC2> YUV_IMAGE_422;
typedef hls::Scalar<3, unsigned char>  YUV_PIXEL3;
typedef hls::Scalar<2, unsigned char>  YUV_PIXEL2;

void imgyuv444to422 (YUV_IMAGE_444& yuv444, YUV_IMAGE_422& yuv422, int rows, int cols);
void simple_yuv444to422 (AXI_STREAM3& video_in, AXI_STREAM2& video_out);

void videoflow (AXI_STREAM3& video_in, AXI_STREAM2& video_out)
{
#pragma HLS INTERFACE axis port=video_out bundle=OUTPUT_STREAM
#pragma HLS INTERFACE axis port=video_in  bundle=INPUT_STREAM
	YUV_IMAGE_444 img_in;
	YUV_IMAGE_422 img_out;
#pragma HLS DATAFLOW
	AXIvideo2Mat(video_in, img_in);
	imgyuv444to422(img_in, img_out, rows, cols);
	Mat2AXIvideo(img_out, video_out);
}

void imgyuv444to422 (YUV_IMAGE_444& yuv444, YUV_IMAGE_422& yuv422, int rows, int cols)
{
	YUV_PIXEL3 p1, p2;
	YUV_PIXEL2 p1n, p2n;
	for(int row = 0;row < rows; row++)
	{
		for(int col = 0; col < cols; col+=2)
		{
#pragma HLS PIPELINE II=1
			yuv444.read(p1);
			yuv444.read(p2);
			p1n.val[0] = p1.val[0];
			p1n.val[1] = p1.val[1];
			p2n.val[0] = p2.val[0];
			p2n.val[1] = p1.val[2];
			yuv422.write(p1n);
			yuv422.write(p2n);
		}
	}
}


//void simple_yuv444to422 (AXI_STREAM3& video_in, AXI_STREAM2& video_out)
//{
//	YUV_PIXEL3 p1, p2;
//	YUV_PIXEL2 p1n, p2n;
//	for(int row = 0;row < rows; row++)
//	{
//		for(int col = 0; col < cols; col+=2)
//		{
//#pragma HLS PIPELINE II=1
//			video_in >> p1;
//			video_in >> p2;
//			p1n.val[0] = p1.val[0];
//			p1n.val[1] = p1.val[1];
//			p2n.val[0] = p2.val[0];
//			p2n.val[1] = p1.val[2];
//			video_out << p1n;
//			video_out << p2n;
//		}
//	}
//}
