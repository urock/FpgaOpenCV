//#ifndef _IMAGE_COMPARE_H_
//#define _IMAGE_COMPARE_H_

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;

void golden_yuv4442yuv422(Mat& yuv444, Mat& yuv422)
{
//    Mat yuv444(rgb.rows, rgb.cols, CV_8UC3);
//    cvtColor(rgb, yuv444, CV_BGR2YUV);
    // chroma subsampling: yuv444 -> yuv422;
    for (int row = 0; row < yuv444.rows; row++) {
        for (int col = 0; col < yuv444.cols; col+=2) {
            Vec3b p0_in = yuv444.at<Vec3b>(row, col);
            Vec3b p1_in = yuv444.at<Vec3b>(row, col+1);
            Vec2b p0_out, p1_out;
            p0_out.val[0] = p0_in.val[0];
            p0_out.val[1] = p0_in.val[1];
            p1_out.val[0] = p1_in.val[0];
            p1_out.val[1] = p0_in.val[2];
            yuv422.at<Vec2b>(row, col) = p0_out;
            yuv422.at<Vec2b>(row, col+1) = p1_out;
        }
    }
}



//#endif
