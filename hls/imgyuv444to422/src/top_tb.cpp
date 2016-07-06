#include "hls_opencv.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>

#ifndef _IMAGE_COMPARE_H_
#define _IMAGE_COMPARE_H_
//#include "../common/image_utils.h"
#define INPUT_FILENAME "/home/matvich/yuv444to422/solution1/bard-wallpaper.jpg"
//#define OUTPUT_FILENAME_GOLDEN "golden-image.jpg"
//#define OUTPUT_FILENAME "image.jpg"

typedef hls::Scalar<3, unsigned char>  YUV_PIXEL3;
typedef hls::Scalar<2, unsigned char>  YUV_PIXEL2;
typedef hls::stream<ap_axiu<16,1,1,1> > AXI_STREAM2;
typedef hls::stream<ap_axiu<24,1,1,1> > AXI_STREAM3;

extern void videoflow (AXI_STREAM3& video_in, AXI_STREAM2& video_out);
extern void golden_yuv4442yuv422(cv::Mat& yuv444, cv::Mat& yuv422);
int image_compare(cv::Mat &o, cv::Mat &g);

int main()
{
//	YUV_PIXEL3 temp;
//	temp.val [0] = 1;
//	temp.val [1] = 2;
//	temp.val [2] = 3;
//	YUV_PIXEL2 temp1;
//	YUV_PIXEL2 temp2;
//	hls::Mat <1920, 1080, HLS_8UC3> init;
//	hls::Mat <1920, 1080, HLS_8UC2> final;
//	AXI_STREAM3 v_in;
//	AXI_STREAM2 v_out;
//	for (int i = 0; i < 1080; i++)
//	{
//		for (int j = 0; j < 1920; j++)
//		{
//			init.write(temp);
//		}
//	}
	//READING IMAGE
	cv::Mat in_image = cv::imread(INPUT_FILENAME);

	//NEW MATRIXES
	cv::Mat yuv444(in_image.rows, in_image.cols, CV_8UC3);
	cv::Mat yuv422(in_image.rows, in_image.cols, CV_8UC2);
	cv::Mat yuv422_g(in_image.rows, in_image.cols, CV_8UC2);

	//CONVERTING RGB TO YUV444
	cv::cvtColor(in_image, yuv444, CV_BGR2YUV);

	//HLS
	AXI_STREAM3 stream_yuv444;
	AXI_STREAM2 stream_yuv422;
	cvMat2AXIvideo(yuv444, stream_yuv444);


	videoflow(stream_yuv444, stream_yuv422);
	AXIvideo2cvMat(stream_yuv422, yuv422);

	//GOLDEN
	golden_yuv4442yuv422(yuv444, yuv422_g);

	return image_compare(yuv422, yuv422_g);


//	hls::Mat2AXIvideo(init, v_in);
//	videoflow(v_in, v_out);
//	hls::AXIvideo2Mat(v_out, final);
//	final.read(temp1);
//	final.read(temp2);
//	printf("%d, %d    %d, %d", temp1.val[0], temp1.val[1], temp2.val[0], temp2.val[1]);

}

using namespace cv;

int image_compare(Mat &o, Mat &g)
{
//        Mat o = imread(output_image);
//        Mat g = imread(golden_image);
//        assert(o.rows == g.rows && o.cols == g.cols);
//        assert(o.channels() == g.channels() && o.depth() == g.depth());
        printf("rows = %d, cols = %d, channels = %d, depth = %d\n", o.rows, o.cols, o.channels(), o.depth());
        int flag = 0;
        for (int i = 0; i < o.rows && flag == 0; i++)
        {
            for (int j = 0; j < o.cols && flag == 0; j++)
            {
                for (int k = 0; k < o.channels(); k++)
                {
                    unsigned char p_o = (unsigned char)*(o.data + o.step[0]*i + o.step[1]*j + k);
                    unsigned char p_g = (unsigned char)*(g.data + g.step[0]*i + g.step[1]*j + k);
                    if (p_o != p_g)
                    {
                        printf("First mismatch found at row = %d, col = %d\n", i, j);
                        printf("(channel%2d) output:%5d, golden:%5d\n", k, p_o, p_g);
                        flag = 1;
                        break;
                    }
                }
            }
        }
        if (flag)
            printf("Test Failed!\n");
        else
            printf("Test Passed!\n");

        return flag;
    }

#endif

